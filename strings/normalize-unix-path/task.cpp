#include <string>
#include <iterator>
#include <vector>

using namespace std;

string normalize(string_view path) {

    int path_size = path.size(), i = 0;

    string nstr = "";
    vector<int> ans;

    if(path_size == 1){
        if(path[0] == '.')
            return ".";
        return "/";
    }else if(path[0] == '.' && path[1] == '.'){
        nstr.push_back('.');
        nstr.push_back('.');
        i = 2;
        while(i < path_size && (path[i] == '/' || path[i] == '.')){
            if(path[i] == '.' && path[i - 1] == '.') {
                nstr.push_back('.');
                nstr.push_back('.');
            }else if(path[i] == '/')
                nstr.push_back('/');
            i++;
        }
    }


    int k = 1;
    while(i < path_size){
        if(path[i] == '/'){
            nstr.push_back('/');
            while(i + k < path_size && (path[i + k] == '.' || path[i + k] == '/')){
                k++;
            }
            i += k;
            k = 1;
        }
        if(i < path_size)
            nstr.push_back(path[i]);
        i++;
    }
    i = 0;
    int j;
    int nstr_size = nstr.size();
    string temp_world, next_world;
    while(i < nstr_size){
        while(i < nstr_size && (nstr[i] == '/' || nstr[i] == '.'))
            i++;
        if(i < nstr_size)
            while(i < nstr_size && nstr[i] != '/' ) {
                temp_world += nstr[i];
                j = i;
                i++;
            }
        break;
    }
    while(i < nstr_size){
        while(i < nstr_size && (nstr[i] == '/' || nstr[i] == '.'))
            i++;
        if(i < nstr_size)
            while(i < nstr_size && nstr[i] != '/' ) {
                next_world += nstr[i];
                i++;
            }
        if(next_world == temp_world)
            nstr = string(nstr, 0, j) + string(nstr, i, nstr.size() - i);
        temp_world = next_world;
        j = i;
        next_world ="";

    }

    if(nstr[nstr_size - 1] == '/' && nstr_size > 1)
        nstr = string(nstr, 0, nstr_size - 1);
    return nstr;

}

/*  while(i < path_size){
        if(path[i] == '.'){
            if(i < path_size - 1 && path[i + 1] == '.'){
                if(i == 0){
                    nstr += "..";
                    while ((path[i] == '/' or path[i] == '.') && i < path_size) {
                        nstr += path[i];
                        i++;
                    }
                    if(i - 2 >= 0 && path[i - 1] == '.' && path[i - 2] != '.'){
                        nstr = string(nstr, i - 2);
                    }
                }
            }else if(i < path_size - 1 && path[i + 1] != '.' && i == 0)
        }
    }*/
