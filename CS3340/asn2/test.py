def count_connected_parts(image):
    def dfs(image, i, j):
        print(i, j)
        if i < 0 or i >= len(image) or j < 0 or j >= len(image[0]) or image[i][j] != '+':
            return
        image[i][j] = '#'  # Marking visited
        directions = [(1, 0), (-1, 0), (0, 1), (0, -1),
                      (1, 1), (-1, -1), (1, -1), (-1, 1)]
        for dx, dy in directions:
            dfs(image, i + dx, j + dy)

    count = 0
    for i in range(len(image)):
        for j in range(len(image[0])):
            if image[i][j] == '+':
                count += 1
                dfs(image, i, j)
    return count


# Example usage:
image = [
    [' ', ' ', '+', '+', ' '],
    [' ', ' ', '+', '+', ' '],
    [' ', '+', ' ', ' ', ' '],
    [' ', '+', ' ', '+', '+'],
    [' ', ' ', '+', '+', ' '],
]

print("Number of connected parts:", count_connected_parts(image))


def read_image_from_file(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
        grid = [[c for c in line.strip()] for line in lines]
    return grid


def main():
    filename = input("Enter the filename containing the binary image: ")
    grid = read_image_from_file(filename)
    print(grid[0])
    connected_components = count_connected_parts(grid)
    print("Number of connected components:", connected_components)


if __name__ == "__main__":
    main()
