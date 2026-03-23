#include "Educationmodel.h"



EducationModel::EducationModel(QObject *parent) : QAbstractListModel(parent)
{}

int EducationModel::rowCount(const QModelIndex &parent) const{
    if(parent.isValid())
        return 0;

    return m_educations.size();

}
QVariant EducationModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid() || index.row() >= m_educations.size()){
        return QVariant();
    }
    const auto &education = m_educations.at(index.row());
    switch (role) {
    case IdRole:            return education.id;
    case InstitutionRole:   return education.institution;
    case DegreeRole:        return education.degree;
    case FieldRole:        return education.field;
    case LocationRole:      return education.location;
    case StartYearRole:     return education.startYear;
    case EndYearRole:       return education.endYear;
    case DescriptionRole:   return education.description;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> EducationModel::roleNames() const {

    QHash<int, QByteArray> roles;
    roles[IdRole]               = "id";
    roles[InstitutionRole]      = "institution";
    roles[FieldRole]           = "field";
    roles[DegreeRole]           = "degree";
    roles[LocationRole]         = "location";
    roles[StartYearRole]        = "startYear";
    roles[EndYearRole]          = "endYear";
    roles[DescriptionRole]      = "description";
    return roles;
}
void EducationModel::setEducations(const QList<Education> educations){
    beginResetModel();
    m_educations = educations;
    endResetModel();
}
