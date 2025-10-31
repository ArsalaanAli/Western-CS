#include <nds.h>

#include <stdio.h>
#include <malloc.h>
#include <math.h>


//structs for the mesh
typedef struct Vertex {
	float x;
	float y;
	float z;
	float u;
	float v;
} Vertex;

typedef struct Triangle {
	int i0;
	int i1;
	int i2;
} Triangle;

//mesh for the object
typedef struct Mesh {
	const Vertex* vertices;
	int vertexCount;
	const Triangle* triangles;
	int triangleCount; // each triangle is one polygon for our cap
} Mesh;

//bounding box for the object
typedef struct BoundingBox {
	float x;
	float y;
	float z;
	float width;
	float height;
	float depth;
} BoundingBox;

//texture for the object
typedef struct Texture {
	const u8* data;
	int width;
	int height;
	int format;
	int textureSize;
	int textureId;
	bool uploaded;

	Texture() : data(NULL), width(0), height(0), format(GL_RGB), 
	            textureSize(TEXTURE_SIZE_128), textureId(0), uploaded(false) {}
} Texture;

//scene node for scene graph, each of these nodes holds an object for the scene
//recursively render through these nodes to render the entire scene
class SceneNode {
public:
	float posX;
	float posY;
	float posZ;
	float rotX;
	float rotY;
	float rotZ;

	float scaleX;
	float scaleY;
	float scaleZ;

	int colorRGB15;    
	Texture* texture;  
	const Mesh* mesh;  
	BoundingBox bounds; 
	static const int MAX_CHILDREN = 16;
	SceneNode* children[MAX_CHILDREN];
	int childCount;

	SceneNode()
		: posX(0), posY(0), posZ(0), rotX(0), rotY(0), rotZ(0),
		  scaleX(1.0f), scaleY(1.0f), scaleZ(1.0f),
		  colorRGB15(RGB15(31,31,31)), texture(NULL), mesh(NULL), childCount(0) {
		bounds.x = bounds.y = bounds.z = 0.0f;
		bounds.width = bounds.height = bounds.depth = 0.0f;
		for(int i = 0; i < MAX_CHILDREN; i++) children[i] = NULL;
	}

	//add a node as a child of this node
	bool addChild(SceneNode* child) {
		if(childCount >= MAX_CHILDREN) return false;
		children[childCount++] = child;
		return true;
	}

	//remove a node from the children of this node
	bool removeChild(SceneNode* child) {
		if(child == NULL) return false;
		
		for(int i = 0; i < childCount; i++) {
			if(children[i] == child) {
				
				for(int j = i; j < childCount - 1; j++) {
					children[j] = children[j + 1];
				}
				children[childCount - 1] = NULL;
				childCount--;
				return true;
			}
		}
		
		//child not found
		return false;
	}

	//functions for transforming this object
	void setPosition(float x, float y, float z) {
		posX = x; posY = y; posZ = z;
	}

	void setRotation(float x, float y, float z) {
		rotX = x; rotY = y; rotZ = z;
	}

	void setScale(float x, float y, float z) {
		scaleX = x; scaleY = y; scaleZ = z;
	}

	void translate(float dx, float dy, float dz) {
		posX += dx; posY += dy; posZ += dz;
	}

	void rotate(float dx, float dy, float dz) {
		rotX += dx; rotY += dy; rotZ += dz;
	}

	void scale(float sx, float sy, float sz) {
		scaleX *= sx; scaleY *= sy; scaleZ *= sz;
	}

	//set the texture for this object
	void setTexture(Texture* tex) {
		texture = tex;
	}
};

//hardcoded cube mesh for sample scene
static const Vertex CUBE_VERTICES[] = {
	// pos                       // uv
	{ -0.5f, -0.5f, -0.5f,       0.0f, 1.0f },
	{  0.5f, -0.5f, -0.5f,       1.0f, 1.0f },
	{  0.5f,  0.5f, -0.5f,       1.0f, 0.0f },
	{ -0.5f,  0.5f, -0.5f,       0.0f, 0.0f },
	{ -0.5f, -0.5f,  0.5f,       0.0f, 1.0f },
	{  0.5f, -0.5f,  0.5f,       1.0f, 1.0f },
	{  0.5f,  0.5f,  0.5f,       1.0f, 0.0f },
	{ -0.5f,  0.5f,  0.5f,       0.0f, 0.0f },
};

static const Triangle CUBE_TRIS[] = {
	{0, 1, 2}, {0, 2, 3},
	{4, 6, 5}, {4, 7, 6},
	{0, 3, 7}, {0, 7, 4},
	{1, 5, 6}, {1, 6, 2},
	{0, 4, 5}, {0, 5, 1},
	{3, 2, 6}, {3, 6, 7},
};

static const Mesh CUBE_MESH = {
	CUBE_VERTICES,
	(int)(sizeof(CUBE_VERTICES) / sizeof(CUBE_VERTICES[0])),
	CUBE_TRIS,
	(int)(sizeof(CUBE_TRIS) / sizeof(CUBE_TRIS[0]))
};

//rendering functions

//apply the transform to this object before rendering
static inline void applyNodeTransform(const SceneNode* node) {
	glTranslatef(node->posX, node->posY, node->posZ);
	glRotateZ(node->rotZ);
	glRotateY(node->rotY);
	glRotateX(node->rotX);
	glScalef(node->scaleX, node->scaleY, node->scaleZ);
}

//check if the object is visible
static inline bool cullNodeByBounds(const SceneNode* node) {
	int visible = BoxTestf(
		node->bounds.x,
		node->bounds.y,
		node->bounds.z,
		node->bounds.width,
		node->bounds.height,
		node->bounds.depth
	);
	return visible == 0;
}

//upload the texture to VRAM
static inline void uploadTexture(Texture* tex) {
	if(tex == NULL || tex->data == NULL || tex->uploaded) return;
	
	glGenTextures(1, &tex->textureId);	glBindTexture(0, tex->textureId);
	glTexImage2D(0, 0, (GL_TEXTURE_TYPE_ENUM)tex->format, tex->textureSize, tex->textureSize, 0, TEXGEN_TEXCOORD, tex->data);
	tex->uploaded = true;
}

//render the mesh
static inline void drawMesh(const Mesh* mesh, int colorRGB15, Texture* texture, int* ioPolygonCount, const int polygonCap) {
	//early return if the mesh is not valid or polygon count is reached
	if(mesh == NULL) return;
	if(*ioPolygonCount >= polygonCap) return;

	int trisToDraw = mesh->triangleCount;
	//draw the triangles
	for(int t = 0; t < trisToDraw; t++) {
		//early return if polygon count is reached
		if(*ioPolygonCount >= polygonCap) break;
		const Triangle tri = mesh->triangles[t];
		const Vertex v0 = mesh->vertices[tri.i0];
		const Vertex v1 = mesh->vertices[tri.i1];
		const Vertex v2 = mesh->vertices[tri.i2];

        glBegin(GL_TRIANGLES);
			//use texture coordinates if texture is available
			if(texture != NULL && texture->uploaded) {
				// Set color to white for texture to show fully
				glColor3f(1.0f, 1.0f, 1.0f);
				//convert uv from 0-1 range to t16 format, because DS requires fixed point formats
				int texSize = texture->width;
				//set the texture sampliing coordinates to be rendered by the DS
				GFX_TEX_COORD = TEXTURE_PACK(inttot16((int)(v0.u * texSize)), inttot16((int)((1.0f - v0.v) * texSize)));
				//draw the vertices
				glVertex3f(v0.x, v0.y, v0.z);
				GFX_TEX_COORD = TEXTURE_PACK(inttot16((int)(v1.u * texSize)), inttot16((int)((1.0f - v1.v) * texSize)));
				glVertex3f(v1.x, v1.y, v1.z);
				GFX_TEX_COORD = TEXTURE_PACK(inttot16((int)(v2.u * texSize)), inttot16((int)((1.0f - v2.v) * texSize)));
				glVertex3f(v2.x, v2.y, v2.z);
			} else {
				//if no texture, set color inside glBegin (taken from boxtest example)

				//RGB15 is a function that comes from libnds, it converts a 32 bit color to a 15 bit color
				//mask to get 5 bit values (since 31 is 11111)
				int r5 = (colorRGB15) & 31;

				//shift to get green and blue bits
				int g5 = (colorRGB15 >> 5) & 31;
				int b5 = (colorRGB15 >> 10) & 31;
				float rf = (float)r5 / 31.0f;
				float gf = (float)g5 / 31.0f;
				float bf = (float)b5 / 31.0f;
				glColor3f(rf, gf, bf);
				//draw the vertices
				glVertex3f(v0.x, v0.y, v0.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
			}
		glEnd();

		(*ioPolygonCount)++;
	}
}

static void renderNodeRecursive(SceneNode* node, int* ioPolygonCount, const int polygonCap) {
	//early return if polygon count reached
	if(*ioPolygonCount >= polygonCap) return;

	glPushMatrix();
	
	//test bounds before rendering
	if(cullNodeByBounds(node)) {
		glPopMatrix(1);
		return;
	}
	
	applyNodeTransform(node);

    //set the polygon format for this node
    glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);

	//handle rendering if there is a texture
	if(node->texture != NULL && node->texture->data != NULL) {
		//upload the texture to VRAM
		uploadTexture(node->texture);
		//if uploaded, enable the texture and bind to texture id
		if(node->texture->uploaded && node->texture->textureId > 0) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(0, node->texture->textureId);
		} else {
			glDisable(GL_TEXTURE_2D);
		}
	} else {
		//if no texture, disable
		glDisable(GL_TEXTURE_2D);
		//unbind the texture
		glBindTexture(0, 0);
	}

	//render the mesh
	drawMesh(node->mesh, node->colorRGB15, node->texture, ioPolygonCount, polygonCap);
	
	//recurse into children
	for(int i = 0; i < node->childCount; i++) {
		if(node->children[i] != NULL) renderNodeRecursive(node->children[i], ioPolygonCount, polygonCap);
		if(*ioPolygonCount >= polygonCap) break;
	}

	glPopMatrix(1);
}

//generating a checkerboard texture for sample scene
static u8* generateCheckerboardTexture(int size) {
	int pixelCount = size * size;
	u8* textureData = (u8*)malloc(pixelCount * 2);
	
	u16 white = RGB15(31, 31, 31);
	u16 green = RGB15(0, 31, 0);
	
	int checkSize = size / 8;  // 8x8 checkerboard pattern
	
	for(int y = 0; y < size; y++) {
		for(int x = 0; x < size; x++) {
			int checkX = x / checkSize;
			int checkY = y / checkSize;
			//white if x + y are even, green otherwise
			u16 color = ((checkX + checkY) % 2 == 0) ? white : green;
			int idx = (y * size + x) * 2;
			//set the color of the pixel (masking lower 8 bits)
			textureData[idx] = color & 0xFF;
			//masking upper 8 bits
			textureData[idx + 1] = (color >> 8) & 0xFF;
		}
	}
	
	return textureData;
}

//initializing a cube node for sample scene
static void initCubeNode(SceneNode* node, float sx, float sy, float sz, int colorRGB15) {
	node->mesh = &CUBE_MESH;
	node->colorRGB15 = colorRGB15;
	node->bounds.x = -sx * 0.5f;
	node->bounds.y = -sy * 0.5f;
	node->bounds.z = -sz * 0.5f;
	node->bounds.width = sx;
	node->bounds.height = sy;
	node->bounds.depth = sz;
}


int main() {
	//init code
	lcdMainOnTop();
	consoleDemoInit();

	videoSetMode(MODE_0_3D);

	glInit();
	glEnable(GL_ANTIALIAS);
	glClearColor(0,0,0,31);
	glClearPolyID(63);
	glClearDepth(0x7FFF);
	glViewport(0,0,255,191);

	vramSetBankA(VRAM_A_TEXTURE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 256.0f / 192.0f, 0.1f, 20.0f);

	//root scene node for sample scene (this holds the scene graph)
	SceneNode root;
	root.posX = 0.0f; root.posY = 0.0f; root.posZ = 0.0f;
	root.rotX = 0.0f; root.rotY = 0.0f; root.rotZ = 0.0f;
	root.mesh = NULL; //root node isnt rendered
	root.bounds.x = -100.0f; root.bounds.y = -100.0f; root.bounds.z = -100.0f;
	root.bounds.width = 200.0f; root.bounds.height = 200.0f; root.bounds.depth = 200.0f;

	//untextured red cube A
	static SceneNode cubeA;
	initCubeNode(&cubeA, 3.0f, 3.0f, 3.0f, RGB15(31,0,0));
	cubeA.posX = -2.5f; cubeA.posY = 1.5f; cubeA.posZ = 0.0f;
	cubeA.setTexture(NULL);
	root.addChild(&cubeA);

	//textured green cube B with checkerboard texture
	static SceneNode cubeB;
	initCubeNode(&cubeB, 2.0f, 2.0f, 2.0f, RGB15(0,31,0));
	cubeB.posX = 2.5f; cubeB.posY = 0.0f; cubeB.posZ = 0.0f;
	
	//assign checkerboard texture for cube B
	static Texture cubeBTexture;
	static u8* cubeBTextureData = generateCheckerboardTexture(128);
	cubeBTexture.data = cubeBTextureData;
	cubeBTexture.width = 128;
	cubeBTexture.height = 128;
	cubeBTexture.format = GL_RGB;
	cubeBTexture.textureSize = TEXTURE_SIZE_128;
	cubeBTexture.textureId = 0;
	cubeBTexture.uploaded = false;
	cubeB.setTexture(&cubeBTexture);
	
	//add cube B to the scene graph
	root.addChild(&cubeB);

	//camera transform
	float cameraRotX = 0.0f;
	float cameraRotY = 0.0f;
	float cameraDistance = -5.0f;

	//polygon cap at 4000
	const int POLYGON_CAP = 4000;

	printf("\x1b[1;0HScene Graph Engine\n");


	//main loop
	while(pmMainLoop()) {
		scanKeys();

		int held = keysHeld();

		if(held & KEY_LEFT) cameraRotY += 1.0f;
		if(held & KEY_RIGHT) cameraRotY -= 1.0f;
		if(held & KEY_UP) cameraRotX += 1.0f;
		if(held & KEY_DOWN) cameraRotX -= 1.0f;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(70, 256.0f/192.0f, 0.1f, 20.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotateY(cameraRotY);
		glRotateX(cameraRotX);
		glTranslatef(0.0f, 0.0f, cameraDistance);

		int polygonCount = 0;

		//wait for the geometry engine to be idle before starting a new frame
		while (GFX_STATUS & (1<<27));

		//reset the GL state at start of frame
		glDisable(GL_TEXTURE_2D);
		glBindTexture(0, 0);
		glColor3f(1.0f, 1.0f, 1.0f);
		
		//render the scene graph
		renderNodeRecursive(&root, &polygonCount, POLYGON_CAP);
		

		//write the polygon count to bottom screen
		printf("\x1b[6;0HPolygons: %d / %d   ", polygonCount, POLYGON_CAP);

		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}


