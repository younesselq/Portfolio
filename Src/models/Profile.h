#pragma once

#include <QObject>
#include <QString>
#include <QVariantList>

// Structure légère pour une langue
struct Language {
    QString name;
    QString level;
};

class ProfileModel : public QObject
{
    Q_OBJECT

    // Chaque Q_PROPERTY est accessible directement en QML
    // via le nom de la propriété : profile.firstName, profile.email, etc.

    Q_PROPERTY(QString   firstName     READ firstName     NOTIFY profileChanged)
    Q_PROPERTY(QString   lastName      READ lastName      NOTIFY profileChanged)
    Q_PROPERTY(QString   fullName      READ fullName      NOTIFY profileChanged)
    Q_PROPERTY(QString   title         READ title         NOTIFY profileChanged)
    Q_PROPERTY(QString   email         READ email         NOTIFY profileChanged)
    Q_PROPERTY(QString   phone         READ phone         NOTIFY profileChanged)
    Q_PROPERTY(QString   location      READ location      NOTIFY profileChanged)
    Q_PROPERTY(QString   driverLicense READ driverLicense NOTIFY profileChanged)
    Q_PROPERTY(QString   summary       READ summary       NOTIFY profileChanged)

    // QVariantList = seul type que QML peut itérer pour les objets composites
    // Chaque élément sera un QVariantMap { "name": "Français", "level": "Courant" }
    Q_PROPERTY(QVariantList languages READ languages NOTIFY profileChanged)

public:
    explicit ProfileModel(QObject *parent = nullptr);

    // --- Getters ---
    QString     firstName()     const { return m_firstName; }
    QString     lastName()      const { return m_lastName; }
    QString     fullName()      const { return m_firstName + " " + m_lastName; }
    QString     title()         const { return m_title; }
    QString     email()         const { return m_email; }
    QString     phone()         const { return m_phone; }
    QString     location()      const { return m_location; }
    QString     driverLicense() const { return m_driverLicense; }
    QString     summary()       const { return m_summary; }
    QVariantList languages()    const { return m_languages; }

    // --- Chargement depuis le DataLoader ---
    void setProfile(const QString   &firstName,
                    const QString   &lastName,
                    const QString   &title,
                    const QString   &email,
                    const QString   &phone,
                    const QString   &location,
                    const QString   &driverLicense,
                    const QString   &summary,
                    const QList<Language> &languages);

signals:
    // Un seul signal pour toutes les propriétés :
    // quand profileChanged est émis, QML rebinde tout automatiquement
    void profileChanged();

private:
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
