#include "modelex.h"
modelex::modelex(QObject *parent): QAbstractTableModel(parent)
{
    QFile fileIn("data.txt");
    QFile fileOut("illuminance.txt");
    //�������ļ���ֻ����ʽ
    if(!fileIn.open(QIODevice::ReadOnly))
    {
        qDebug() << "�ļ���ʧ�ܣ�";
    }
    //������ļ���ֻд��ʽ
    if(!fileOut.open(QIODevice::WriteOnly))
    {
        qDebug() << "�ļ���ʧ�ܣ�";
    }
    qDebug() << "�ļ��򿪳ɹ���";
    QJsonParseError jsonParserError;
    while(!fileIn.atEnd())
    {
        QJsonDocument jsonDocument = QJsonDocument::fromJson(fileIn.readLine(), &jsonParserError);
        if (!jsonDocument.isNull() && jsonParserError.error == QJsonParseError::NoError )//error!=QJsonParseError::NoError�ж��ļ��Ƿ�����
        {
            if(jsonDocument.isObject())
            {
                QJsonObject jsonObject = jsonDocument.object();
                if(jsonObject.contains("actioncode") && (jsonObject.value( "actioncode" ) != "actioncode") &&
                        (jsonObject.value( "actioncode" ) != "readerHeartInfo"))
                {
                    //����postdata��ֵ��Ҳ��һ��Json����
                    QJsonValue postdataValue = jsonObject.value("postdata");
                    QJsonObject postdataObject = postdataValue.toObject();
                    //�����Զ���Json����
                    QJsonObject json;
                    json.insert("actioncode", jsonObject.value("actioncode"));
                    json.insert("sensorID", postdataObject.value("sensorID"));
                    //������������Ϣ
                    if(jsonObject.value( "actioncode" ) == "moistureReturn")//1
                    {
                        json.insert("moisture", postdataObject.value("moisture"));
                        json.insert("temperature", postdataObject.value("temperature"));
                        QString b1;//toDouble ת��ΪQString�����ٽ��
                        double a1 = postdataObject.value("moisture").toDouble();
                        b1=QString::number(a1,10,5);
                        data1<<QString(b1);
                        QString b2;//toDouble ת��ΪQString�����ٽ��
                        double a2 = postdataObject.value("temperature").toDouble();
                        b2=QString::number(a2,10,5);
                        data2<<QString(b2);
                    }
                    else if(jsonObject.value( "actioncode" ) == "temphumidityReturn")//2
                    {
                        json.insert("temperature", postdataObject.value("temperature"));
                        json.insert("humidity", postdataObject.value("humidity"));
                        QString b1;//toDouble ת��ΪQString�����ٽ��
                        double a1 = postdataObject.value("temperature").toDouble();
                        b1=QString::number(a1,10,5);
                        data1<<QString(b1);
                        QString b2;//toDouble ת��ΪQString�����ٽ��
                        double a2 = postdataObject.value("humidity").toDouble();
                        b2=QString::number(a2,10,5);
                        data2<<QString(b2);
                    }
                    else if(jsonObject.value( "actioncode" ) == "soilPHReturn")//3
                    {
                        json.insert("soilPH", postdataObject.value("soilPH"));
                        QString b1;//toDouble ת��ΪQString�����ٽ��
                        double a1 = postdataObject.value("soilPH").toDouble();
                        b1=QString::number(a1,10,5);
                        data1<<QString(b1);
                        data2<<QString("");
                    }
                    else if(jsonObject.value( "actioncode" ) == "windspeedReturn")//4
                    {
                        json.insert("windspeed", postdataObject.value("windspeed"));
                        QString b1;//toDouble ת��ΪQString�����ٽ��
                        double a1 = postdataObject.value("windspeed").toDouble();
                        b1=QString::number(a1,10,5);
                        data1<<QString(b1);
                        data2<<QString("");
                    }
                    else if(jsonObject.value( "actioncode" ) == "pm2dot5Return")//5
                    {
                        json.insert("pm2dot5", postdataObject.value("pm2dot5"));
                        QString b1;//toDouble ת��ΪQString�����ٽ��
                        double a1 = postdataObject.value("pm2dot5").toDouble();
                        b1=QString::number(a1,10,5);
                        data1<<QString(b1);
                        data2<<QString("");
                    }
                    else if(jsonObject.value( "actioncode" ) == "rainsnowReturn")//6
                    {
                        json.insert("rainsnow", postdataObject.value("rainsnow"));
                        QString b1;//toDouble ת��ΪQString�����ٽ��
                        double a1 = postdataObject.value("pm2dot5").toDouble();
                        b1=QString::number(a1,10,5);
                        data1<<QString(b1);
                        data2<<QString("");
                    }
                    else if(jsonObject.value( "actioncode" ) == "rainsnowReturn")//7
                    {
                        json.insert("rainsnow", postdataObject.value("rainsnow"));
                        QString b1;//toDouble ת��ΪQString�����ٽ��
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
                    //�����ͼ��
                    weapon<<QString(jsonObject.value( "actioncode" ).toString());
                    time<<QString(postdataObject.value("timestamp").toString());
                    SensorId<<QString(postdataObject.value("sensorID").toString());
                    //QJsonDocument::Compact //�����Json�ļ�Ϊ������
                    //QJsonDocument::Indented //�����Json�ļ�Ϊ��ɢ�� ��Ĭ�ϣ�
                    //fileOut.write(outDocument.toJson(QJsonDocument::Compact)); //�����Json�ļ�Ϊ������
                    fileOut.write(outDocument.toJson(QJsonDocument::Indented)); //�����Json�ļ�Ϊ��ɢ��
                    fileOut.write("\n");
                }
            }
        }
    }
    fileOut.close();
    fileIn.close();
   /* armyMap[1]=tr("�վ�");
    armyMap[2]=tr("����");
    armyMap[3]=tr("½��");
    armyMap[4]=tr("����½ս��");
    weaponTypeMap[1]=tr("��ը��");
    weaponTypeMap[2]=tr("ս����");
    weaponTypeMap[3]=tr("����ĸ��");
    weaponTypeMap[4]=tr("����");
    weaponTypeMap[5]=tr("ֱ����");
    weaponTypeMap[6]=tr("̹��");
    weaponTypeMap[7]=tr("���ܹ�����");
    weaponTypeMap[8]=tr("����ս��");*/
    populateModel();
}
void modelex::populateModel()
{
    header<<tr("Actioncode")<<tr("SensorID")<<tr("Data1")<<tr("Data2")<<tr("Timestamp");
    //army<<1<<2<<3<<4<<2<<4<<3<<1;
   // weaponType<<1<<3<<5<<7<<4<<8<<6<<2;
   // weapon<<tr("B-2")<<QString("�����ȼ�")<<tr("������")<<tr("�Ʒ伶")<<tr("�������˼�")<<tr("AAAV")<<tr("M1A1")<<tr("F-22");
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
