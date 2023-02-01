//
// Created by Jason Fu on 2/1/2023.
//

#include "vector_.h"

void Vector_::vector_for_file(std::vector<Note *> note_vector)
    {
        QFile file;
        file.setFileName("log.txt");   //保存到本地地址
        if(file.open(QIODevice::WriteOnly| QIODevice::Text))
        {
            QTextStream stream(&file);
            for(int i=0;i<note_vector.size();i++)
            {
                stream<<note_vector.at(i)->finish<<" ";
                stream<<note_vector.at(i)->Thing<<" ";
                stream<<note_vector.at(i)->Time<<" ";
                stream<<note_vector.at(i)->Date<<" ";
                stream<<note_vector.at(i)->ddl<<" ";
                stream<<note_vector.at(i)->note<<" "<<"#\n";  //n n n n n n #\n
                //
            }
        }
    }