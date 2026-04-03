#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QtQml/qqml.h>

struct Education {
    int     id;
    QString institution;
    QString degree;
    QString specialization;
    QString location;
    int     startYear;
    int     endYear;
    QString level;
};

class EducationModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    enum EducationRoles {
        IdRole = Qt::UserRole + 1,
        InstitutionRole,
        DegreeRole,
        SpecializationRole,
        LocationRole,
        StartYearRole,
        EndYearRole,
        LevelRole
    };
    Q_ENUM(EducationRoles)

    static EducationModel *create(QQmlEngine *, QJSEngine *)
    {
        return instance();
    }

    static EducationModel *instance()
    {
        static EducationModel inst;
        return &inst;
    }

    int      rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setEducations(const QList<Education> &educations);

private:
    explicit EducationModel(QObject *parent = nullptr)
        : QAbstractListModel(parent) {}

    QList<Education> m_educations;
};
