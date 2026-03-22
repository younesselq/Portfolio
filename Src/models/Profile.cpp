#include "ProfileModel.h"

ProfileModel::ProfileModel(QObject *parent)
    : QObject(parent)
{}

// ─────────────────────────────────────────────
// setProfile — appelé par le DataLoader après
// avoir parsé le profile.json
// ─────────────────────────────────────────────
void ProfileModel::setProfile(const QString      &firstName,
                              const QString      &lastName,
                              const QString      &title,
                              const QString      &email,
                              const QString      &phone,
                              const QString      &location,
                              const QString      &driverLicense,
                              const QString      &summary,
                              const QList<Language> &languages)
{
    m_firstName     = firstName;
    m_lastName      = lastName;
    m_title         = title;
    m_email         = email;
    m_phone         = phone;
    m_location      = location;
    m_driverLicense = driverLicense;
    m_summary       = summary;

    // Conversion QList<Language> → QVariantList
    // pour que QML puisse itérer avec un Repeater
    // et accéder aux champs via modelData.name / modelData.level
    m_languages.clear();
    for (const Language &lang : languages) {
        QVariantMap map;
        map["name"]  = lang.name;
        map["level"] = lang.level;
        m_languages.append(map);
    }

    // Notifie QML : toutes les propriétés sont à jour
    emit profileChanged();
}
