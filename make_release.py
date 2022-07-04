from distutils.command.config import config
import os 
import sys
import zipfile

dll_path = './build/cmake-build-debug'
manual_selection = True
extra_files = ['README.md','changelog.md']
config_file = './src/base/config.json'

def get_dll_file_path():
    files = os.listdir(dll_path)
    dlls = [f for f in files if f.endswith('dll')]
    if len(dlls) == 0:
        print("No dll files")
        exit(-1)
    
    select_index = 0
    print("Here are all the dlls")
    for i in range(len(dlls)):
        print('[%d]:  %s' % (i, dlls[i]))
    if manual_selection and len(dlls) > 1:
        select_index = input("Choose one")
    return dlls[0]


def create_zip(dll_name :str):
    version = dll_name[:-4]
    print("Version is %s" % version)
    release_zip_file = zipfile.ZipFile(
        version + '.zip', 'w', compresslevel=6, compression=zipfile.ZIP_DEFLATED)
    

    for f in extra_files:
        release_zip_file.write(f,arcname=f)
    release_zip_file.write(dll_path +'/'+ version + '.dll', arcname='plugins/'+version+'.dll')
    release_zip_file.write(config_file, arcname='plugins/trapdoor/config.json')
    release_zip_file.write(dll_path + '/' + version + '.pdb', arcname= 'plugins/'+version+'.pdb')
    release_zip_file.close()

if __name__ == "__main__":    
    arg_len = len(sys.argv)
    if arg_len !=3 and arg_len != 1:
        print("Error args len")
        exit(-1)
    if arg_len == 3:
        dll_path = sys.argv[1]
        manual_selection = int(sys.argv[2]) == 1

    print("Dll path is ", dll_path)
    print("manual_selection is set to", manual_selection)

    p = get_dll_file_path()
    create_zip(p)

     