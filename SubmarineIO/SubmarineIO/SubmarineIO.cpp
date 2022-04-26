#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <zconf.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <vector>
#include <io.h>
#include <algorithm>
#define int long long int


void showCompressedStr(char* x)
{
    int l = _msize(x) / sizeof(char);
    for (int i = 0; i < l; i++)
    {
        printf("%02d ", x[i]);
    }
}

void writeStringToFile(std::string a,std::string fileName)
{
    std::ofstream out(fileName);
    if (out.is_open())
    {
        out << a;
        out.close();
    }
}

void writeCompressedStringToFile(char* a,int length,char* path)
{
    FILE* fileP;
    fopen_s(&fileP, path, "wb");
    if (fileP == NULL)
    {
        printf("openFailed");
        return;
    }
    //int siz = _msize(a);
    //fwrite(a, length*sizeof(char)+sizeof(char), 1, fileP);
    for (int i = 0; i < length+5; i++)
    {
        fputc(a[i], fileP);
    }
    fclose(fileP);
    return;
}
char* readCompressedStringFromFile(char* path)
{
    FILE* fileP;
    char* ls = (char*)malloc(1024*1024*10);
    memset(ls, 0, 1024*1024*10/sizeof(char));
    fopen_s(&fileP, path, "rb");
    if (fileP == NULL)
    {
        printf("openFailed");
        return NULL;
    }
    int i;
    for (i = 0; i >= 0; i++)
    {
        if (feof(fileP))
        {
            ls[i-1] = 0;
            break;
        }
        ls[i] = fgetc(fileP);
    }
    //printf("length:%d", i+1);
    fclose(fileP);
    return ls;
}

std::string readFileIntoString(char* filename)
{
    std::ifstream ifile(filename);
    //将文件读入到ostringstream对象buf中
    std::ostringstream buf;
    char ch;
    while (buf && ifile.get(ch))
        buf.put(ch);
    //返回与流对象buf关联的字符串
    return buf.str();
}



struct ComedString
{
    char* ch;
    int le;
};
int gzCompress(const char* src, int srcLen, char* dest, int destLen)
{
    z_stream c_stream;
    int err = 0;
    int windowBits = 15;
    int GZIP_ENCODING = 16;

    if (src && srcLen > 0)
    {
        c_stream.zalloc = (alloc_func)0;
        c_stream.zfree = (free_func)0;
        c_stream.opaque = (voidpf)0;
        if (deflateInit2(&c_stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
            windowBits | GZIP_ENCODING, 8, Z_DEFAULT_STRATEGY) != Z_OK) return -1;
        c_stream.next_in = (Bytef*)src;
        c_stream.avail_in = srcLen;
        c_stream.next_out = (Bytef*)dest;
        c_stream.avail_out = destLen;
        while (c_stream.avail_in != 0 && c_stream.total_out < destLen)
        {
            if (deflate(&c_stream, Z_NO_FLUSH) != Z_OK) return -1;
        }
        if (c_stream.avail_in != 0) return c_stream.avail_in;
        for (;;) {
            if ((err = deflate(&c_stream, Z_FINISH)) == Z_STREAM_END) break;
            if (err != Z_OK) return -1;
        }
        if (deflateEnd(&c_stream) != Z_OK) return -1;
        return c_stream.total_out;
    }
    return -1;
}


int gzDecompress(const char* src, int srcLen, const char* dst, int dstLen) {
    z_stream strm;
    strm.zalloc = NULL;
    strm.zfree = NULL;
    strm.opaque = NULL;

    strm.avail_in = srcLen;
    strm.avail_out = dstLen;
    strm.next_in = (Bytef*)src;
    strm.next_out = (Bytef*)dst;

    int err = -1, ret = -1;
    err = inflateInit2(&strm, MAX_WBITS + 16);
    if (err == Z_OK) {
        err = inflate(&strm, Z_FINISH);
        if (err == Z_STREAM_END) {
            ret = strm.total_out;
        }
        else {
            inflateEnd(&strm);
            return err;
        }
    }
    else {
        inflateEnd(&strm);
        return err;
    }
    inflateEnd(&strm);
    return err;
}

ComedString comStr(char* src)
{
    ComedString out;
    int size_src = strlen(src);
    out.ch = (char*)malloc(size_src * 10);
    memset(out.ch, 0, size_src * 10);
    out.le = gzCompress(src, size_src,out.ch, size_src * 10);
    if (out.le <= 0)
    {
        printf("error");
    }
    return out;
}
char* uncomStr(char* src)
{
    int length1 = _msize(src)/sizeof(char);
    //printf("lth1:%d\n", length1);
    char* uncompressed = (char*)malloc(length1*10);
    memset(uncompressed, 0, length1*10);
    int ret = gzDecompress(src, length1, uncompressed, length1*10);
    return uncompressed;
}

std::string TCHAR2STRING(TCHAR* STR )
{ 

 int iLen = WideCharToMultiByte(CP_ACP, 0,STR, -1, NULL, 0, NULL, NULL);   

 char* chRtn = new char[iLen * sizeof(char)];  

 WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL); 

std::string str(chRtn); 

return str;

}

std::vector<std::string> files;

void getFiles(std::string path, std::vector<std::string>& files)
{
    long   hFile = 0;
    struct _finddata_t fileinfo;
    std::string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                //if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    //getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
            }
            else
            {
                //files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                files.push_back(fileinfo.name);
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}




signed main() 
{
    printf("Barotrauma Submarine convertor 0.1.0 Return_dirt 2022/3/30\n");
    printf("Enter your command\n");
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(NULL, szPath, MAX_PATH);
    std::string Dir = TCHAR2STRING(szPath);
    std::reverse(Dir.begin(), Dir.end());
    Dir.erase(0,16);
    std::reverse(Dir.begin(), Dir.end());
    std::cout << Dir << std::endl;
    

    printf("1:*.sub==>*.xml\n2:*.xml==>*.sub\n");
    int cho;
    std::cin >> cho;
    if (cho == 1)
    {
        getFiles(Dir, files);
        for (int i = 0; i < files.size(); i++)
        {
            if (files[i].substr(files[i].length() - 3) == "sub")
            {
                std::cout << files[i] << std::endl;
                
                char* out = readCompressedStringFromFile((char*)files[i].c_str());
                std::string outStr = files[i].substr(0, files[i].length() - 3) + "xml";
                writeStringToFile(uncomStr((char*)out), (char*)outStr.c_str());
                std::cout << outStr << std::endl;
            }
            
        }
    }
    if (cho == 2)
    {
        getFiles(Dir, files);
        for (int i = 0; i < files.size(); i++)
        {
            if (files[i].substr(files[i].length() - 3) == "xml")
            {
                std::cout << files[i] << std::endl;
                std::string a = readFileIntoString((char*)files[i].c_str());
                ComedString out = comStr((char*)a.c_str());
                std::string outStr = files[i].substr(0, files[i].length() - 3) + "sub";
                writeCompressedStringToFile(out.ch, out.le, (char*)outStr.c_str());
                std::cout << outStr << std::endl;
            }
        }
    }
    
    return 0;

}

signed m_ain()
{
    const char* a = "nmmmmmmdwdnmd";
    comStr((char *)a);
    return 0;
}