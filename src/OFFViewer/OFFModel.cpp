#include"include/OFFViewer/OFFModel.h"
#include<QTextStream>
#include<QFile>
#include<QDebug>

QString readNextLine(QTextStream &stream){
    QString str;

    while (str.isEmpty()) {
        if (stream.atEnd()) {
            throw "Unexpected end of file!";
        }
        str = stream.readLine();
        str = str.trimmed();
    }

    return str;
}

QStringList string2Tokens(QString &str){

    str.replace('\t', ' ');
    return str.split(' ', QString::SkipEmptyParts);
}

OFFModel::OFFModel(const QString &filename){
    QFile file(filename);
    QTextStream stream(&file);
    if(!file.open(QFile::ReadOnly)){
        throw "Unable to open file!";
    }

    QString line = readNextLine(stream);
    if(line!="OFF"){
        throw "Wrong file formate!";
    }

    line = readNextLine(stream);
    QStringList tokens = string2Tokens(line);
    if(tokens.size()!=3){
        throw "Can't read vertex, polygon and edge numbers!";
    }

    int nVertices = tokens[0].toInt();
    int nFaces = tokens[1].toInt();

    for(int i = 0; i < nVertices; i ++){
        line = readNextLine(stream);
        tokens = string2Tokens(line);
        if(tokens.size() < 3){
            throw "Can't find all vertex components!";
        }
        QVector3D a(tokens[0].toFloat(), tokens[1].toFloat(), tokens[2].toFloat());
        mVertices.append(a);
    }

    for(int i = 0; i < nFaces; i++){
        line = readNextLine(stream);
        tokens = string2Tokens(line);
        int n = tokens[0].toInt();
        if(tokens.size() != n + 1 || tokens.size() < 4){
            throw "Can't parse face data!";
        }
        mFaces.append(n);

        QVector3D normal = QVector3D::normal(
                mVertices[tokens[1].toInt()],
                mVertices[tokens[2].toInt()],
                mVertices[tokens[3].toInt()]);

        for(int j = 0; j < n; j ++){
            mData.append(mVertices[tokens[j+1].toInt()].x());
            mData.append(mVertices[tokens[j+1].toInt()].y());
            mData.append(mVertices[tokens[j+1].toInt()].z());
            mData.append(normal.x());
            mData.append(normal.y());
            mData.append(normal.z());
        }
    }
    normalize();
}

int OFFModel::count(){
    return mData.size();
}

const float* OFFModel::constData(){
    return mData.constData();
}

void OFFModel::normalize(){
    float max = mData[0], min = mData[0];
    int mod = 0;
    for(int i = 0; i < mData.size(); i ++){
        //skip normal vertex
        if(mod%6 < 3){
            if(mData[i] > max)
                max = mData[i];
            if(mData[i] < min)
                min = mData[i];
        }
    }
    mod = 0;
    for(int i = 0; i < mData.size(); i ++){
        if(mod % 6 < 3)
            mData[i] /= (max - min);
    }
}
