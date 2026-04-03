#include "Educationmodel.h"




int EducationModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_educations.size();
}

QVariant EducationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_educations.size())
        return QVariant();

    const Education &edu = m_educations.at(index.row());

    switch (role) {
    case IdRole:             return edu.id;
    case InstitutionRole:    return edu.institution;
    case DegreeRole:         return edu.degree;
    case SpecializationRole: return edu.specialization;
    case LocationRole:       return edu.location;
    case StartYearRole:      return edu.startYear;
    case EndYearRole:        return edu.endYear;
    case LevelRole:          return edu.level;
    default:                 return QVariant();
    }
}

QHash<int, QByteArray> EducationModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole]             = "id";
    roles[InstitutionRole]    = "institution";
    roles[DegreeRole]         = "degree";
    roles[SpecializationRole] = "specialization";
    roles[LocationRole]       = "location";
    roles[StartYearRole]      = "startYear";
    roles[EndYearRole]        = "endYear";
    roles[LevelRole]          = "level";
    return roles;
}

void EducationModel::setEducations(const QList<Education> &educations)
{
    beginResetModel();
    m_educations = educations;
    endResetModel();
}
