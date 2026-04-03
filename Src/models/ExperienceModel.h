#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QtQml/qqml.h>

struct Experience {
    int         id;
    QString     company;
    QString     client;
    QString     role;
    QString     location;
    QString     startDate;
    QString     endDate;
    bool        current;
    QString     domain;
    QString     description;
    QStringList tasks;
    QStringList technologies;
};

class ExperienceModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    enum ExperienceRoles {
        IdRole = Qt::UserRole + 1,
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

    static ExperienceModel *create(QQmlEngine *, QJSEngine *)
    {
        return instance();
    }

    static ExperienceModel *instance()
    {
        static ExperienceModel inst;
        return &inst;
    }

    int      rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setExperiences(const QList<Experience> &experiences);

private:
    explicit ExperienceModel(QObject *parent = nullptr)
        : QAbstractListModel(parent) {}

    QList<Experience> m_experiences;
};
