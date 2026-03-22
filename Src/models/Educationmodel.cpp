#include "Educationmodel.h"



EducationModel::EducationModel(Qobject *parent) : QAbstractListModel(parent)
{}

int EducationModel::rowCount(const QModelIndex &parent = QModelIndex()){
    if(parent.isValid())
        return;

    return m_educations.size();

}
QVariant EducationModel::data(const QModelIndex &index, int role){
    if(!index.isValid() || index.row() >= m_educations.size()){
        return QVariant();
    }
    const auto &education = m_educations.at(index.row());
    switch (role) {
    case Idrole:            return education.id;
    case InstitutionRole:   return education.institution;
    case DegreeRole:        return education.degree;
    case FieledRole:        return education.field;
    case LocationRole:      return education.location;
    case StartYearRole:     return education.startYear;
    case EndYearRole:       return education.endYear;
    case DescriptionRole:   return education.description;
    default:
        QVariant();
    }
}

QHash<int, QByteArray> EducationModel::roleNames() {

    QHash<int, QByteArray> roles;
    roles[IdRole]               = "id";
    roles[InstitutionRole]      = "institution";
    roles[FieledRole]           = "field";
    roles[DegreeRole]           = "degree";
    roles[LocationRole]         = "location";
    roles[StartYearRole]        = "startYear";
    roles[EndYearRole]          = "endYear";
    roles[DescriptionRole]      = "description";

}
void EducationModel::setEducations(QList<Education> educations) {
    beginResetModel();
    m_educations = educations;
    endResetModel();
}
