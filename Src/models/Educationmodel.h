#ifndef EDUCATIONMODEL_H
#define EDUCATIONMODEL_H

#include <QObject>
#include <QAbstractListModel>

struct Education
{
    int id;
    QString institution;
    QString degree;
    QString field;
    QString location;
    QString startYear;
    QString endYear;
    QString description;

};

class EducationModel : QAbstractListModel
{
    Q_OBJECT
public:

    enum EducataionRoles{
        IdRole     = Qt::UserRole + 1,
        InstitutionRole,
        DegreeRole,
        FieldRole,
        LocationRole,
        StartYearRole,
        EndYearRole,
        DescriptionRole
    };
    Q_ENUM(EducataionRoles)

    explicit EducationModel(QObject *parent=nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override ;
    QHash<int, QByteArray> roleNames() const override;
    void setEducations(const QList<Education> educations);
private:
    QList<Education> m_educations;
};

#endif // EDUCATIONMODEL_H
