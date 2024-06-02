/*
    325195774
    netaco432@gmail.com
*/

#ifndef ALGORITHMS_H
#define ALGORITHMS_H


#include <iostream>
#include "Graph.hpp"

namespace ariel {

    class Algorithms {

    public:

        static bool is_BFS_cover_all(Graph g, size_t start);

        static bool isConnected(Graph g); // האלגוריתם מקבל גרף ומחזיר 1 אם הגרף קשיר (אחרת מחזיר 0).


        static vector<int> dijkstra(Graph g, size_t start, vector<size_t>& parent);

        static string shortestPath(Graph g, size_t start, size_t end); // האלגוריתם מקבל גרף, קודקוד התחלה וקודקוד סיום ומחזיר את המסלול הקל ביותר (במקרה שהגרף לא ממושקל - הקצר ביותר) בין שני הקודקודים. במידה ואין מסלול כזה, האלגוריתם יחזיר -1.

        
        static bool dfs(Graph g, size_t node, vector<bool>& visited, vector<size_t>& parent, string& cycle);

        static string isContainsCycle(Graph g); // האלגוריתם מקבל גרף ומדפיס מעגל כלשהו. אם לא קיים מעגל בגרף, האלגוריתם יחזיר 0.

        static string isBipartite(Graph g); // האלגוריתם מקבל גרף ומחזיר את החלוקה של הגרף לגרף דו-צדדי. אם אי אפשר לחלק את הגרף, האלגוריתם יחזיר 0.

        static bool negativeCycle(Graph g); // האלגוריתם מקבל גרף ומוצא מעגל שלילי (כלומר מעגל שסכום המשקלים של הצלעות שלילי). אם לא קיים מעגל כזה, האלגוריתם ידפיס שלא קיים מעגל שלילי.

    };

}

#endif

