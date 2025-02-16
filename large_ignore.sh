#!/bin/bash

# 定义文件大小阈值 (50MB)
max_size=$((50 * 1024 * 1024))

# 输出大文件列表到 .gitignore
echo "Scanning for files larger than 50MB..."

# 查找大于 50MB 的文件并处理
find . -type f -size +${max_size}c | while read file; do
    # 确保文件路径不重复加入 .gitignore
    if ! grep -q "$file" .gitignore; then
        echo "Ignoring large file: $file"
        echo "$file" >> .gitignore
    fi
done

echo "Large files have been added to .gitignore."
