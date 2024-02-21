def process_obj_file_with_scaling(input_path, output_path, scale_factor):
    vertices = []
    triangles = []

    with open(input_path, 'r') as file:
        for line in file:
            tokens = line.strip().split()

            if not tokens:
                continue

            if tokens[0] == 'v':
                # 读取顶点并进行缩放
                scaled_vertex = [float(coord) * scale_factor for coord in tokens[1:]]
                vertex_line = f"v {' '.join(map(str, scaled_vertex))}\n"
                vertices.append(vertex_line)
            elif tokens[0] == 'f':
                # 将包含法线和材质信息的f行转换为只包含顶点索引的形式
                vertex_indices_only = [vertex.split('/')[0] for vertex in tokens[1:]]
                # # 移除重复顶点索引
                # vertex_indices_only = list(dict.fromkeys(vertex_indices_only))

                if len(vertex_indices_only) > 2:
                    # 如果是多边形面，将其转换为三角形面
                    for i in range(1, len(vertex_indices_only) - 1):
                        triangle = f"f {' '.join([vertex_indices_only[0], vertex_indices_only[i], vertex_indices_only[i + 1]])}\n"
                        triangles.append(triangle)
                else:
                    # 如果是三角形面，保持不变
                    triangles.append(line)

    with open(output_path, 'w') as output_file:
        # 写入所有顶点
        output_file.write("# Vertices\n")
        for vertex in vertices:
            output_file.write(vertex)

        # 写入所有三角形面
        output_file.write("\n# Triangles\n")
        for triangle in triangles:
            output_file.write(triangle)

if __name__ == "__main__":
    input_file_path = "input.obj"  # 替换成你的输入文件路径
    output_file_path = "output.obj"  # 替换成你的输出文件路径
    scale_factor = 1  # 替换成你想要的缩放因子

    process_obj_file_with_scaling(input_file_path, output_file_path, scale_factor)

    print("Processing completed.")
