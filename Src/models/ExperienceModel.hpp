#pragma once
#include <QAbstractListModel>
#include <QList>
#include <QObject>
#include <QVariant>

// Structure qui représente une expérience (miroir exact du JSON)

struct Experience
{
    int id;
    QString company;
    QString client;
    QString role;
    QString location;
    QString     startDate;
    QString     endDate;
    bool        current;
    QString     domain;
    QString     description;
    QStringList tasks;
    QStringList technologies;

};

class ExperienceModel : QAbstractListModel{

    Q_OBJECT

public:
    // --- Roles QML ---
    // Chaque Role correspond à une propriété accessible depuis QML
    // ex: model.role, model.company, etc.
    enum ExperienceRoles{
        IdRole      = Qt::UserRole + 1,
        CompanyRole,
        ClientRole,
        RoleRole,
        LocationRole,
        StartDateRole,
        EndDateRole,
        CurrentRole,
        DomainRole,
        DescriptionRole,
        TasksRole,
        TechnologiesRole
    };

    Q_ENUM(ExperienceRoles)

    explicit ExperienceModel(QObject *parent=nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data (const QModelIndex &index, int role) const override;
    QHash<int , QByteArray> roleNames() const override;

    // --- Méthode pour charger les données depuis le DataLoader ---
    void setExperiences (const QList<Experience> &experiences);

private:
    QList<Experience> m_experiences;




};

