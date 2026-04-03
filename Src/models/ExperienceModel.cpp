#include "ExperienceModel.h"


// ─────────────────────────────────────────────
// rowCount — nombre de lignes dans le modèle
// QML appelle ça automatiquement pour savoir
// combien d'éléments il doit afficher
// ─────────────────────────────────────────────
int ExperienceModel::rowCount(const QModelIndex &parent) const
{
    // Convention Qt : si parent est valide, on est dans un arbre
    // Pour une liste plate, on retourne 0 dans ce cas
    if (parent.isValid())
        return 0;
    return m_experiences.size();

}
// ─────────────────────────────────────────────
// data — renvoie la valeur d'un champ pour
// un index donné et un role donné
// QML appelle ça pour chaque propriété de chaque item
// ─────────────────────────────────────────────
QVariant ExperienceModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row()>= m_experiences.size())
    {
        return QVariant();
    }
    const auto &exp = m_experiences.at(index.row());
    switch (role) {
    case IdRole:           return exp.id;
    case CompanyRole:      return exp.company;
    case ClientRole:       return exp.client;
    case RoleRole:         return exp.role;
    case LocationRole:     return exp.location;
    case StartDateRole:    return exp.startDate;
    case EndDateRole:      return exp.endDate;
    case CurrentRole:      return exp.current;
    case DomainRole:       return exp.domain;
    case DescriptionRole:  return exp.description;
    case TasksRole:        return exp.tasks;        // QStringList → array QML
    case TechnologiesRole: return exp.technologies; // QStringList → array QML
    default:               return QVariant();
    }

}

// ─────────────────────────────────────────────
// roleNames — mappe chaque Role à un nom QML
// C'est ce nom que tu utilises dans le QML :
//   model.company, model.jobRole, model.current...
// ─────────────────────────────────────────────
QHash<int, QByteArray> ExperienceModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole]           = "id";
    roles[CompanyRole]      = "company";
    roles[ClientRole]       = "client";
    roles[RoleRole]         = "jobRole";      // "role" est réservé en QML → "jobRole"
    roles[LocationRole]     = "location";
    roles[StartDateRole]    = "startDate";
    roles[EndDateRole]      = "endDate";
    roles[CurrentRole]      = "current";
    roles[DomainRole]       = "domain";
    roles[DescriptionRole]  = "description";
    roles[TasksRole]        = "tasks";
    roles[TechnologiesRole] = "technologies";
    return roles;
}

// ─────────────────────────────────────────────
// setExperiences — appelé par le DataLoader
// pour injecter les données JSON parsées
// ─────────────────────────────────────────────
void ExperienceModel::setExperiences(const QList<Experience> &experiences)
{
    // beginResetModel/endResetModel notifie QML
    // que toutes les données ont changé → rebind automatique
    beginResetModel();
    m_experiences = experiences;
    endResetModel();
}

