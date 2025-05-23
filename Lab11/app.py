import os

from flask import Flask, request
import random
import string

app = Flask(__name__)

path = "file_sandbox"

@app.get('/get_files')
def get_files():
    folder_path = "" if request.args.get('folder_path') is None else request.args.get('folder_path')

    complete_path = os.path.join(path, folder_path)
    # return the list of files in the directory
    files = os.listdir(complete_path)
    return {'files': files}

@app.get("/get_file_content")
def get_file_content():
    file_name = request.args.get('file_name')

    # read the file in the directory
    with open(os.path.join(path, file_name), 'r') as f:
        content = f.read()
    return {'content': content}

@app.post('/create_file')
def create_file():
    requestJson = request.get_json(force=True)

    file_name: str = "" if requestJson.get('file_name') is None else requestJson.get('file_name')
    file_content: str = requestJson.get('file_content')

    if file_name == "":
        file_name = ''.join(random.choices(string.ascii_letters + string.digits, k=10))

    with open(os.path.join(path, file_name), 'w') as f:
        f.write(file_content)
    return {'message': 'File created successfully'}

@app.post('/create_folder')
def create_folder():
    folder_name = request.args.get('folder_name')

    # create the folder in the directory
    os.makedirs(os.path.join(path, folder_name), exist_ok=True)
    return {'message': 'Folder created successfully'}

@app.delete('/delete_file')
def delete_file():
    file_name = request.args.get('file_name')

    # delete the file in the directory
    os.remove(os.path.join(path, file_name))
    return {'message': 'File deleted successfully'}

@app.patch('/update_file')
def update_file():
    requestJson = request.get_json(force=True)

    file_name: str = requestJson.get('file_name')
    file_content: str = requestJson.get('file_content')

    # update the file in the directory
    with open(os.path.join(path, file_name), 'w') as f:
        f.write(file_content)
    return {'message': 'File updated successfully'}


if __name__ == '__main__':
    app.run()
