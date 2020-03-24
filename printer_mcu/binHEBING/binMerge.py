# -*- coding: utf-8 -*-
#!C:\Users\Administrator\AppData\Local\Programs\Python\Python38
import os
import shutil
import struct
import string
import sys
# 列出指定目录下的所有文件 （包含子文件的子文件
# 定义个函数，来列出目录下所有文件的路径
def list_son_dir(dir_path,soure_file):
    #获取某个目录下是所有文件名
    file_names = os.listdir(dir_path)
    # 遍历每个文件名
    for file_name in file_names:
        # 拼接出这个文件的完整路径
        file_path  = os.path.join(dir_path,file_name)
        # 把路径打印出来
        print(file_path)
        strings = str(file_path)
        if soure_file in strings:
        #if strings.find(soure_file) != -1 :
        	print("Find the target file: " + str(strings))
        	return strings
        # 判断这个路径是不是一个文件夹
        #if os.path.isdir(file_path):
            # 如果是文件夹
        #    list_son_dir(file_path)
        #else:
        #    #如果不是文件夹（是一个文件）,什么都不做
        #    pass

# 调用这个函数
class SearchFile(object):
  def __init__(self,path='.'):
    self._path=path
    self.abspath=os.path.abspath(self._path) # 默认当前目录
    print("Current search root directory: " + self.abspath)
  #def findfile(self,keyword,root):
  def findfile(self,keyword):
    filelist=[]
    for root,dirs,files in os.walk(self.abspath):
      for name in files:  
        fitfile=filelist.append(os.path.join(root, name))
        #print(fitfile)
        #print(os.path.join(root, name))
        #print(filelist)
        #print('...........................................')
    c = keyword.find('.')
    filetype = keyword[c:]
    #print(filetype)
    for i in filelist:  
      if os.path.isfile(i) and filetype in i:
        print(i)
      if keyword in os.path.split(i)[1]:
        print('Yes!',i) # 绝对路径
        return i
      #else:
      #  print('......no keyword!')
    return ''
  def __call__(self):
    while True:
      workpath=input('Do you want to work under the current folder? Y/N:')
      if(workpath == ''):
        break
      if workpath=='y' or workpath=='Y':
        root=self.abspath # 把当前工作目录作为工作目录
        print('当前工作目录：',root)
        dirlist=os.listdir() # 列出工作目录下的文件和目录
        print(dirlist)
      else:
        root=input('please enter the working directory:')
        print('当前工作目录：',root)
        keyword=input('the keyword you want to find:')
        if(keyword==''): 
          break
        self.findfile(keyword,root) # 查找带指定字符的文件
#if __name__ == '__main__':
 

#bin_iap_path = list_son_dir('../binHEBING',"_IAP.bin")
#bin_app_path = list_son_dir('../',"_app.bin")
#bin_result_path = bin_app_path[:-7] + 'link.bin'
#bin_iap_path = '../binHEBING/STM32F4xx_IAP.bin'
#bin_app_path = '../Smart_Cabinet_app.bin'
#bin_result_path = '../Smart_Cabinet_link.bin'
search_root_patch = '../'
search_current_patch = '.'
env_dist = os.environ

length = len(sys.argv)
if length >= 2:
  fromelf_patch = sys.argv[1] + "\\fromelf.exe"
  print("......Fromelf patch are input from outside......")
else:
  fromelf_patch = env_dist.get('FROMELF') + "\\fromelf.exe" 
  print("......Fromelf patch are input from environment variable......")
print("Fromelf target patch: " + fromelf_patch)

search = SearchFile(search_current_patch)
axf_current_path = search.findfile('.axf')
if len(axf_current_path) != 0:
  print("Search target axf file: " + axf_current_path)
  generate_bin_name = axf_current_path.split("\\")[-1]
  generate_bin_name = generate_bin_name[:-4]
  generate_bin_patch = search_root_patch + generate_bin_name + ".bin"
  print("Generate target bin file: " + generate_bin_patch)
  fromelf = "%s \"%s\" \"%s\" \"%s\" \"%s\""%(fromelf_patch,axf_current_path, "--bin", "--output",generate_bin_patch )
  os.system(fromelf)
else:
  pass

search = SearchFile(search_root_patch)
app_axf_path = search.findfile('app.axf')
if len(app_axf_path) != 0:
  print("Search target app.axf file: " + app_axf_path)
  generate_bin_name = app_axf_path.split("\\")[-1]
  generate_bin_name = generate_bin_name[:-4]
  generate_bin_patch = search_root_patch + generate_bin_name + ".bin"
  print("Generate target app.bin file: " + generate_bin_patch)
  #env_dist = os.environ
  #fromelf_patch = env_dist.get('FROMELF') + "\\fromelf.exe"
  #print("Fromelf target patch: " + fromelf_patch)
  fromelf = "%s \"%s\" \"%s\" \"%s\" \"%s\""%(fromelf_patch,app_axf_path, "--bin", "--output",generate_bin_patch )
  os.system(fromelf)
else:
  pass

bin_iap_path = search.findfile('_IAP.bin')
bin_app_path = search.findfile('_app.bin')
bin_result_path = bin_app_path[:-7] + 'link.bin'

offset1 = 0x00000000
offset2 = 0x00004000
if len(bin_iap_path) != 0 and len(bin_app_path) != 0:
  print("We have IAP.bin file and app.bin file,now starting merge...")
  shutil.copyfile(bin_iap_path,bin_result_path)
  bin_iap = open(bin_iap_path,'rb')
  bin_app = open(bin_app_path,'rb')
  bin_merge = open(bin_result_path, 'ab')

  app_size = os.path.getsize(bin_app_path)
  bin_result_size = os.path.getsize(bin_result_path)

  final_size = offset2 + app_size

  offset = bin_result_size
  value_default = struct.pack('B', 0x00)

  while offset < final_size:
      if offset == offset2:
          data = bin_app.read()
          bin_merge.write(data)
          offset = bin_merge.tell()
      else:
          bin_merge.write(value_default)
          offset = bin_merge.tell()
  print("Congratulation!: IAP.bin file and app.bin has been merged...")        
  bin_iap.close()
  bin_app.close()
  bin_merge.close()
else:
  print("soure bin file is not find,merge error") 