#include "modelex.h"
modelex::modelex(QObject *parent): QAbstractTableModel(parent)
{
    QFile fileIn("data.txt");
    QFile fileOut("illuminance.txt");
    //打开输入文件，只读方式
    if(!fileIn.open(QIODevice::ReadOnly))
    {
        qDebug() << "文件打开失败！";
    }
    //打开输出文件，只写方式
    if(!fileOut.open(QIODevice::WriteOnly))
    {
        qDebug() << "文件打开失败！";
    }
    qDebug() << "文件打开成功！";
    QJsonParseError jsonParserError;
    while(!fileIn.atEnd())
    {
        QJsonDocument jsonDocument = QJsonDocument::fromJson(fileIn.readLine(), &jsonParserError);
        if (!jsonDocument.isNull() && jsonParserError.error == QJsonParseError::NoError )//error!=QJsonParseError::NoError判断文件是否完整
        {
            if(jsonDocument.isObject())
            {
                QJsonObject jsonObject = jsonDocument.object();
                if(jsonObject.contains("actioncode") && (jsonObject.value( "actioncode" ) != "actioncode") &&
                        (jsonObject.value( "actioncode" ) != "readerHeartInfo"))
                {
                    //解析postdata的值，也是一个Json对象
                    QJsonValue postdataValue = jsonObject.value("postdata");
                    QJsonObject postdataObject = postdataValue.toObject();
                    //构建自定的Json数据
                    QJsonObject json;
                    json.insert("actioncode", jsonObject.value("actioncode"));
                    json.insert("sensorID", postdataObject.value("sensorID"));
                    //传感器数据信息
                    if(jsonObject.value( "actioncode" ) == "moistureReturn")//1
                    {
                        json.insert("moisture", postdataObject.value("moisture"));
                        json.insert("temperature", postdataObject.value("temperature"));
                        QString b1;//toDouble 转化为QString类型再解决
                        double a1 = postdataObject.value("moisture").toDouble();
                        b1=QString::number(a1,10,5);
                        data1<<QString(b1);
                        QString b2;//toDouble 转化为QString类型再解决
                        double a2 = postdataObject.value("temperature").toDouble();
                        b2=QString::number(a2,10,5);
                        data2<<QString(b2);
                    }
                    else if(jsonObject.value( "actioncode" ) == "temphumidityReturn")//2
                    {
                        json.insert("temperature", postdataObject.value("temperature"));
                        json.insert("humidity", postdataObject.value("humidity"));
                        QString b1;//toDouble 转化为QString类型再解决
                        double a1 = postdataObject.value("temperature").toDouble();
                        b1=QString::number(a1,10,5);
                        data1<<QString(b1);
                        QString b2;//toDouble 转化为QString类型再解决
                        double a2 = postdataObject.value("humidity").toDouble();
                        b2=QString::number(a2,10,5);
                        data2<<QString(b2);
                    }
                    else if(jsonObject.value( "actioncode" ) == "soilPHReturn")//3
                    {
                        json.insert("soilPH", postdataObject.value("soilPH"));
                        QString b1;//toDouble 转化为QString类型再解决
                        double a1 = postdataObject.value("soilPH").toDouble();
                        b1=QString::number(a1,10,5);
                        data1<<QString(b1);
                        data2<<QString("");
                    }
                    else if(jsonObject.value( "actioncode" ) == "windspeedReturn")//4
                    {
                        json.insert("windspeed", postdataObject.value("windspeed"));
                        QString b1;//toDouble 转化为QString类型再解决
                        double a1 = postdataObject.value("windspeed").toDouble();
                        b1=QString::number(a1,10,5);
                        data1<<QString(b1);
                        data2<<QString("");
                    }
                    else if(jsonObject.value( "actioncode" ) == "pm2dot5Return")//5
                    {
                        json.insert("pm2dot5", postdataObject.value("pm2dot5"));
                        QString b1;//toDouble 转化为QString类型再解决
                        double a1 = postdataObject.value("pm2dot5").toDouble();
                        b1=QString::number(a1,10,5);
                        data1<<QString(b1);
                        data2<<QString("");
                    }
                    else if(jsonObject.value( "actioncode" ) == "rainsnowReturn")//6
                    {
                        json.insert("rainsnow", postdataObject.value("rainsnow"));
                        QString b1;//toDouble 转化为QString类型再解决
                        double a1 = postdataObject.value("pm2dot5").toDouble();
                        b1=QString::number(a1,10,5);
                        data1<<QString(b1);
                        data2<<QString("");
                    }
                    else if(jsonObject.value( "actioncode" ) == "rainsnowReturn")//7
                    {
                        json.insert("rainsnow", postdataObject.value("rainsnow"));
                        QString b1;//toDouble 转化为QString类型再解决
                        double a1 = postdataObject.value("pm2dot5").toDouble();
                        b1=QString::number(a1,10,5);
                        data1<<QString(b1);
                        data2<<QString("");
                    }
                    else if(jsonObject.value( "actioncode" ) == "illuminanceReturn")//8
                    {
                        json.insert("illuminance", postdataObject.value("illuminance"));
                        data1<<QString(postdataObject.value("illuminance").toString());
                        data2<<QString("");
                    }
                    else;
                    json.insert("timestamp", postdataObject.value("timestamp"));
                    QJsonDocument outDocument;
                    outDocument.setObject(json);
                    //输出到图表
                    weapon<<QString(jsonObject.value( "actioncode" ).toString());
                    time<<QString(postdataObject.value("timestamp").toString());
                    SensorId<<QString(postdataObject.value("sensorID").toString());
                    //QJsonDocument::Compact //输出的Json文件为紧凑型
                    //QJsonDocument::Indented //输出的Json文件为松散型 （默认）
                    //fileOut.write(outDocument.toJson(QJsonDocument::Compact)); //输出的Json文件为紧凑型
                    fileOut.write(outDocument.toJson(QJsonDocument::Indented)); //输出的Json文件为松散型
                    fileOut.write("\n");
                }
            }
        }
    }
    fileOut.close();
    fileIn.close();
   /* armyMap[1]=tr("空军");
    armyMap[2]=tr("海军");
    armyMap[3]=tr("陆军");
    armyMap[4]=tr("海军陆战队");
    weaponTypeMap[1]=tr("轰炸机");
    weaponTypeMap[2]=tr("战斗机");
    weaponTypeMap[3]=tr("航空母舰");
    weaponTypeMap[4]=tr("驱逐舰");
    weaponTypeMap[5]=tr("直升机");
    weaponTypeMap[6]=tr("坦克");
    weaponTypeMap[7]=tr("两栖攻击舰");
    weaponTypeMap[8]=tr("两栖战车");*/
    populateModel();
}
void modelex::populateModel()
{
    header<<tr("Actioncode")<<tr("SensorID")<<tr("Data1")<<tr("Data2")<<tr("Timestamp");
    //army<<1<<2<<3<<4<<2<<4<<3<<1;
   // weaponType<<1<<3<<5<<7<<4<<8<<6<<2;
   // weapon<<tr("B-2")<<QString("尼米兹级")<<tr("阿帕奇")<<tr("黄蜂级")<<tr("阿利伯克级")<<tr("AAAV")<<tr("M1A1")<<tr("F-22");
}
//list
int modelex::columnCount(const QModelIndex &/*parent*/) const
{
    return 5;
}
//row
int modelex::rowCount(const QModelIndex &/*parent*/) const
{
    return 320;
}
QVariant modelex::data(const QModelIndex &index,int role) const
{
    if(!index.isValid())return QVariant();
    if(role==Qt::DisplayRole)
    {
        switch(index.column())
        {
            //case 0:return armyMap[army[index.row()]];break;
            case 0:return weapon[index.row()];break;
            case 1:return SensorId[index.row()];break;
            case 2:return data1[index.row()];break;
            case 3:return data2[index.row()];break;
            case 4:return time[index.row()];break;
            default: return QVariant();
        }
    }
    return QVariant();
}
QVariant modelex::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::DisplayRole&&orientation==Qt::Horizontal)
    {
        return header[section];
    }
    return QAbstractTableModel::headerData(section,orientation,role);
}
