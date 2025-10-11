#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TessellatedPlane {
private:
    GLuint VAO, VBO, EBO;
    GLuint programID;
	GLuint MVPID, viewID, diffuseID, lightDirID, timeID, displacementID, cameraID;

	std::vector<float> vertices;
    std::vector<int> indices;

public:
    TessellatedPlane(float min, float max, float stepsize) {

		MVPID = glGetUniformLocation(programID, "MVP");
        viewID = glGetUniformLocation(programID, "View");
        lightDirID = glGetUniformLocation(programID, "lightDirection");
        timeID = glGetUniformLocation(programID, "time");
		diffuseID = glGetUniformLocation(programID, "diffuseTexture");
		displacementID = glGetUniformLocation(programID, "displacementMap");
		cameraID = glGetUniformLocation(programID, "cameraPosition");
		


        // Generate vertices and indices for a simple plane
        generatePlaneVertices(min, max, stepsize);
        generatePlaneIndices(min, max, stepsize);

        // Generate and bind the Vertex Array Object (VAO)
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // Generate and bind the Vertex Buffer Object (VBO)
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        // Generate and bind the Element Buffer Object (EBO)
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);

        // Set up vertex attribute pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind VAO
        glBindVertexArray(0);

        // Compile and link shaders
        compileShaders();
    }

    void draw(glm::mat4 MVP, glm::mat4 view, float time) {

		glm::vec3 lightpos(5.0f, 5.0f, 5.0f);
        // Use the shader program
        glUseProgram(programID);

        // Bind VAO
        glBindVertexArray(VAO);

        // Set uniform
        glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
		glUniform1f(timeID, time);
	    glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);


		// Draw the tessellated plane
        glPatchParameteri(GL_PATCH_VERTICES, 3); // Set the number of vertices per patch
        glDrawElements(GL_PATCHES, indices.size(), GL_UNSIGNED_INT, 0);

        // Unbind VAO
        glBindVertexArray(0);

        // Unuse the shader program
        glUseProgram(0);
    }

private:
    void generatePlaneVertices(float min, float max, float stepsize) {
        // Generate vertices for a simple plane
        for (float x = min; x <= max; x += stepsize) {
            for (float z = min; z <= max; z += stepsize) {
                vertices.push_back(x);
                vertices.push_back(0.0f);
                vertices.push_back(z);
            }
        }
    }

    void generatePlaneIndices(float min, float max, float stepsize) {
        // Generate indices for a simple plane
        int nCols = (max - min) / stepsize + 1;
        for (int i = 0; i < nCols - 1; ++i) {
            for (int j = 0; j < nCols - 1; ++j) {
                int index = i * nCols + j;
                indices.push_back(index);
                indices.push_back(index + 1);
                indices.push_back(index + nCols);
                indices.push_back(index + nCols);
                indices.push_back(index + 1);
                indices.push_back(index + nCols + 1);
            }
        }
    }

    void compileShaders() {
		// Vertex shader
		const char* vertexShaderSource = R"(
			#version 430 core
			
			// Input from application
			layout(location = 0) in vec3 vertexPosition_modelspace;
			uniform mat4 MVP;
			uniform mat4 View; // View matrix (inverse of the camera matrix)

			// Output to TCS
			out vec3 position_tcs;
			out vec3 eyeDirection; // Output eye direction to be interpolated

			void main() {
				// Output vertex position in world coordinates
				position_tcs = vertexPosition_modelspace;

				// Calculate eye direction in world space
				vec4 worldPosition = View * vec4(vertexPosition_modelspace, 1.0);
				eyeDirection = normalize(-worldPosition.xyz);
			}
		)";

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		checkShaderCompilation(vertexShader);

		// Tessellation control shader
const char *tessControlShaderSource = R"(
    #version 430 core
    layout(vertices = 4) out;

    // Input from vertex shader
    in vec3 position_tcs[];
    in vec2 uv_tcs[];
    in vec3 eyeDirection[];

    // Pass-through variables (arrays)
    out vec3 position_tes[4];
    out vec2 uv_tes[4];
    out vec3 eyeDirection_tes[4];

    void main() {
        int id = gl_InvocationID;

        // Pass input values to TES
        position_tes[id] = position_tcs[id];
        uv_tes[id] = uv_tcs[id];
        eyeDirection_tes[id] = eyeDirection[id];

        // Set tessellation level
        gl_TessLevelOuter[0] = 16.0;
        gl_TessLevelOuter[1] = 16.0;
        gl_TessLevelInner[0] = 16.0;
        gl_TessLevelInner[1] = 16.0;

        // Assign values to output vertices
        gl_out[id].gl_Position = gl_in[id].gl_Position;
    }
)";



		GLuint tessControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
		glShaderSource(tessControlShader, 1, &tessControlShaderSource, NULL);
		glCompileShader(tessControlShader);
		checkShaderCompilation(tessControlShader);

		// Tessellation evaluation shader
		const char *tessEvalShaderSource = R"(
			#version 430 core
			// Input from TCS
			layout(triangles, equal_spacing) in;
			in vec3 position_tes[];
			in vec2 uv_tes[];
			in vec3 eyeDirection_tes[];

			// Output to geometry shader
			out vec3 position_geoshader;
			out vec2 uv_geoshader;
			out vec3 eyeDirection_geoshader;

			void main() {
				float u = gl_TessCoord.x;
				float v = gl_TessCoord.y;

				// Index with gl_InvocationID
				position_geoshader = mix(mix(position_tes[0], position_tes[1], u), position_tes[2], v);
				uv_geoshader = mix(mix(uv_tes[0], uv_tes[1], u), uv_tes[2], v);
				eyeDirection_geoshader = mix(mix(eyeDirection_tes[0], eyeDirection_tes[1], u), eyeDirection_tes[2], v);
			}
		)";


		GLuint tessEvalShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		glShaderSource(tessEvalShader, 1, &tessEvalShaderSource, NULL);
		glCompileShader(tessEvalShader);
		checkShaderCompilation(tessEvalShader);

		// Geometry shader
		const char* geometryShaderSource = R"(
			#version 430 core
			layout(triangles) in;
			layout(triangle_strip, max_vertices = 3) out;

			// Input from TES
			in vec3 position_geoshader[];
			in vec2 uv_geoshader[];
			in vec3 eyeDirection_geoshader[];

			// Output to fragment shader
			out vec3 vertexPosition_worldspace;
			out vec3 normal_worldspace;
			out vec2 uv;
			out vec3 eyeDirection;

			// Uniforms
			uniform float time;
			uniform sampler2D displacementMap;

			// Gerstner wave function
			vec3 Gerstner(vec3 worldpos, float w, float A, float phi, float Q, vec2 D, int N) {
				vec2 xz = worldpos.xz;
				float Dx = D.x;
				float Dz = D.y;
				float waveX = Q * A * Dx * cos(w * Dx * xz.x + w * Dz * xz.y + phi * time);
				float waveY = A * sin(w * Dx * xz.x + w * Dz * xz.y + phi * time);
				float waveZ = Q * A * Dz * cos(w * Dx * xz.x + w * Dz * xz.y + phi * time);
				return vec3(waveX, waveY, waveZ);
			}

			void main() {
				for(int i = 0; i < gl_in.length(); ++i) {
					// Sample displacement map
					float displacement = texture(displacementMap, uv_geoshader[i]).r;
					
					// Apply displacement to vertex position
					vec3 displacedPosition = position_geoshader[i] + vec3(0.0, displacement, 0.0);

					// Apply Gerstner waves
					vec3 waveDisplacement = Gerstner(displacedPosition, 0.5, 0.4, 0.2, 0.5, vec2(0.5, 0.5), 1); // Fill in wave parameters
					vertexPosition_worldspace = displacedPosition + waveDisplacement;
					uv = uv_geoshader[i];
					eyeDirection = eyeDirection_geoshader[i];

					// Calculate normals manually using cross products
					vec3 edge1 = position_geoshader[1] - position_geoshader[0];
					vec3 edge2 = position_geoshader[2] - position_geoshader[0];
					normal_worldspace = normalize(cross(edge1, edge2));

					// Output vertex position and normal
					gl_Position = gl_in[i].gl_Position;
					EmitVertex();
				}
				EndPrimitive();
			}
		)";

		GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometryShaderSource, NULL);
		glCompileShader(geometryShader);
		checkShaderCompilation(geometryShader);

		// Fragment shader
		const char* fragmentShaderSource = R"(
			#version 430 core
			// Input from geometry shader
			in vec3 vertexPosition_worldspace;
			in vec2 uv;
			in vec3 eyeDirection;

			// Output to framebuffer
			out vec4 FragColor;

			// Uniforms
			uniform vec3 lightDirection;
			uniform sampler2D diffuseTexture;

			void main() {
				// Phong-like reflection model
				vec3 normal = normalize(cross(dFdx(vertexPosition_worldspace), dFdy(vertexPosition_worldspace)));
				vec3 lightDir = normalize(lightDirection);
				vec3 viewDir = normalize(eyeDirection);
				vec3 halfwayDir = normalize(lightDir + viewDir);
				float ambientStrength = 0.1;
				vec3 ambient = ambientStrength * texture(diffuseTexture, uv).rgb;
				float diff = max(dot(normal, lightDir), 0.0);
				float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
				vec3 diffuse = diff * texture(diffuseTexture, uv).rgb;
				vec3 specular = spec * texture(diffuseTexture, uv).rgb;
				FragColor = vec4(ambient + diffuse + specular, 1.0);
			}
		)";

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		checkShaderCompilation(fragmentShader);

		// Create shader program and attach shaders
		programID = glCreateProgram();
		glAttachShader(programID, vertexShader);
		glAttachShader(programID, tessControlShader);
		glAttachShader(programID, tessEvalShader);
		glAttachShader(programID, geometryShader);
		glAttachShader(programID, fragmentShader);
		glLinkProgram(programID);

		// Check for linking errors
		GLint linkStatus;
		glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != GL_TRUE) {
			GLint logLength;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<GLchar> log(logLength);
			glGetProgramInfoLog(programID, logLength, NULL, log.data());
			std::cerr << "Error linking program: " << log.data() << std::endl;
			exit(-1);
		}

		// Get uniform location for MVP matrix
		MVPID = glGetUniformLocation(programID, "MVP");

		// Cleanup shaders
		glDeleteShader(vertexShader);
		glDeleteShader(tessControlShader);
		glDeleteShader(tessEvalShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
	}

    void checkShaderCompilation(GLuint shader) {
        GLint compileStatus;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
        if (compileStatus != GL_TRUE) {
            GLint logLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<GLchar> log(logLength);
            glGetShaderInfoLog(shader, logLength, NULL, log.data());
            std::cerr << "Error compiling shader: " << log.data() << std::endl;
            exit(-1);
        }
    }
};
