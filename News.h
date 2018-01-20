//
// Created by Iftach Fridental on 19/01/2018.
//
#pragma once
#ifndef OS4_NEWS_H
#define OS4_NEWS_H

#include <string>

enum NewsType {
    regularNews, weather, sports, DONE
};

class News {
private:
    NewsType type;
    int prod_id;
    int prod_type_id;

public:
    News(NewsType type, int prod_id, int prod_type_id);

    std::string toString() const;

    NewsType getType() { return type; }
};


#endif //OS4_NEWS_H
