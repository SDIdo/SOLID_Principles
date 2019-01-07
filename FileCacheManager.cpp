//
// Created by idox on 1/5/19.
//

#include "FileCacheManager.h"

FileCacheManager::FileCacheManager(string filePath) {
    myFilePath = filePath;
}

void FileCacheManager::set(string problem, string solution) {
    cache[problem] = solution;
}

bool FileCacheManager::check(string problem) {
    return !(cache.find(problem) == cache.end());
}

string FileCacheManager::get(string problem) {
    if (check(problem)){        //check in map
        return this->cache[problem];
    }
    cout << "don't have in the map gotta check in file\n";
    if (read()){
        cout << "got it from the file!\n";
        if (check(problem)){
            return this->cache[problem];
        }
    }
    return "Cache Miss";
}

int FileCacheManager::write() {
//    int WriteFile(std::string fname, std::map<std::string, std::string> *m) {
        int count = 0;
        if (this->cache.empty())
            return 0;

        FILE *fp = fopen(myFilePath.c_str(), "w");
        if (!fp)
            return -errno;

        for(std::map<std::string, std::string>::iterator it = this->cache.begin(); it != this->cache.end(); it++) {
            fprintf(fp, "%s=%s\n", it->first.c_str(), it->second.c_str());
            count++;
        }

        fclose(fp);
        return count;
    }

int FileCacheManager::read() {
        cout << "Entered read\n";
        int count = 0;
        if (access(myFilePath.c_str(), R_OK) < 0)
            return -errno;

        FILE *fp = fopen(myFilePath.c_str(), "r");
        if (!fp)
            return -errno;

//        m->clear();

        char *buf = 0;
        size_t buflen = 0;

        while(getline(&buf, &buflen, fp) > 0) {
            char *nl = strchr(buf, '\n');
            cout << "pointer is: " << nl << "\n";
            if (nl == NULL)
                continue;
            *nl = 0;

            char *sep = strchr(buf, '=');
            if (sep == NULL)
                continue;
            *sep = 0;
            sep++;

            std::string s1 = buf;
            std::string s2 = sep;

            this->cache[s1] = s2;
            cout << s1 << " = " << cache[s1] << "\n";

            count++;
        }

        if (buf)
            free(buf);

        fclose(fp);
//        return count;
}