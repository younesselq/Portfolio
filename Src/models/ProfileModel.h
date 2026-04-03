#pragma once

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QtQml/qqml.h>

struct Language {
    QString name;
    QString level;
};

class ProfileModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QString      firstName     READ firstName     NOTIFY profileChanged)
    Q_PROPERTY(QString      lastName      READ lastName      NOTIFY profileChanged)
    Q_PROPERTY(QString      fullName      READ fullName      NOTIFY profileChanged)
    Q_PROPERTY(QString      title         READ title         NOTIFY profileChanged)
    Q_PROPERTY(QString      email         READ email         NOTIFY profileChanged)
    Q_PROPERTY(QString      phone         READ phone         NOTIFY profileChanged)
    Q_PROPERTY(QString      location      READ location      NOTIFY profileChanged)
    Q_PROPERTY(QString      driverLicense READ driverLicense NOTIFY profileChanged)
    Q_PROPERTY(QString      summary       READ summary       NOTIFY profileChanged)
    Q_PROPERTY(QVariantList languages     READ languages     NOTIFY profileChanged)

public:
    // Appelé par Qt pour créer le singleton QML
    static ProfileModel *create(QQmlEngine *, QJSEngine *)
    {
        return instance();
    }

    // Accès C++ à l'instance unique (utilisé par DataLoader)
    static ProfileModel *instance()
    {
        static ProfileModel inst;
        return &inst;
    }

    QString      firstName()     const { return m_firstName; }
    QString      lastName()      const { return m_lastName; }
    QString      fullName()      const { return m_firstName + " " + m_lastName; }
    QString      title()         const { return m_title; }
    QString      email()         const { return m_email; }
    QString      phone()         const { return m_phone; }
    QString      location()      const { return m_location; }
    QString      driverLicense() const { return m_driverLicense; }
    QString      summary()       const { return m_summary; }
    QVariantList languages()     const { return m_languages; }

    void setProfile(const QString         &firstName,
                    const QString         &lastName,
                    const QString         &title,
                    const QString         &email,
                    const QString         &phone,
                    const QString         &location,
                    const QString         &driverLicense,
                    const QString         &summary,
                    const QList<Language> &languages);

signals:
    void profileChanged();

private:
    // Constructeur privé — seul instance() peut créer l'objet
    explicit ProfileModel(QObject *parent = nullptr) : QObject(parent) {}

    QString      m_firstName;
    QString      m_lastName;
    QString      m_title;
    QString      m_email;
    QString      m_phone;
    QString      m_location;
    QString      m_driverLicense;
    QString      m_summary;
    QVariantList m_languages;
};
