//
// Created by Iftach Fridental on 19/01/2018.
//

#ifndef OS4_NEWS_H
#define OS4_NEWS_H

#include <iostream>
#include <string>

enum NewsType {
    regularNews, weather, sports
};

class News {
private:
    NewsType type;
    int prod_id;
    int prod_type_id;

public:
    News(NewsType type, int prod_id, int prod_type_id);

    friend ostream &operator<<(ostream &outs, const News *obj);

    std::string toString();
};



#endif //OS4_NEWS_H
