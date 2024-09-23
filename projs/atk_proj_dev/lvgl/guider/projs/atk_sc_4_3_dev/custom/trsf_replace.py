import os
import shutil

script_dir = os.path.dirname(os.path.abspath(__file__))  # 获取脚本所在目录的绝对路径

def process_files():
    print("开始处理文件...\n")
    
    # 遍历当前目录及其子目录中的所有文件
    for root, dirs, files in os.walk(script_dir):
        for file in files:
            # 获取文件的完整路径
            file_path = os.path.join(root, file)
            
            # 创建临时文件名（可以添加前缀或后缀）
            temp_file_path = os.path.join(root, f"{file}.temp")
            
            try:
                # 读取源文件内容并写入临时文件
                with open(file_path, 'r', encoding='utf-8') as original_file:
                    content = original_file.read()
                
                with open(temp_file_path, 'w', encoding='utf-8') as temp_file:
                    temp_file.write(content)
                
                # 删除源文件
                os.remove(file_path)
                
                # 将临时文件重命名为源文件名
                os.rename(temp_file_path, file_path)
                
                print(f"处理完成: {file_path}")
            
            except Exception as e:
                print(f"处理文件 {file_path} 时出错: {e}")
        
        print("-" * 50)

process_files()

input("按 Enter 键退出")
