#include "DataLoader.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>

DataLoader::DataLoader(QObject *parent)
    : QObject(parent)
{}

// ─────────────────────────────────────────────
// loadAll — point d'entrée unique
// Appelé une seule fois depuis main.cpp
// après la création de tous les modèles
// ─────────────────────────────────────────────
void DataLoader::loadAll(const QString      &basePath,
                         ProfileModel       *profile,
                         ExperienceModel    *experiences,
                         SkillCategoryModel *hardSkills,
                         SoftSkillModel     *softSkills,
                         EducationModel     *education)
{
    loadProfile    (basePath + "/profile.json",     profile);
    loadExperiences(basePath + "/experiences.json", experiences);
    loadSkills     (basePath + "/skills.json",      hardSkills, softSkills);
    loadEducation  (basePath + "/education.json",   education);

    emit loadingFinished();
}

// ══════════════════════════════════════════════
//  PROFILE
// ══════════════════════════════════════════════
void DataLoader::loadProfile(const QString &path, ProfileModel *model)
{
    QJsonObject root = readJsonObject(path);
    if (root.isEmpty()) return;

    // Langues : tableau d'objets { "name": "...", "level": "..." }
    QList<Language> langs;
    const QJsonArray langArray = root["languages"].toArray();
    for (const QJsonValue &val : langArray) {
        QJsonObject obj = val.toObject();
        Language l;
        l.name  = obj["name"].toString();
        l.level = obj["level"].toString();
        langs.append(l);
    }

    model->setProfile(
        root["firstName"].toString(),
        root["lastName"].toString(),
        root["title"].toString(),
        root["email"].toString(),
        root["phone"].toString(),
        root["location"].toString(),
        root["driverLicense"].toString(),
        root["summary"].toString(),
        langs
        );
}

// ══════════════════════════════════════════════
//  EXPERIENCES
// ══════════════════════════════════════════════
void DataLoader::loadExperiences(const QString &path, ExperienceModel *model)
{
    QJsonArray array = readJsonArray(path);
    if (array.isEmpty()) return;

    QList<Experience> list;
    for (const QJsonValue &val : array) {
        QJsonObject obj = val.toObject();

        Experience exp;
        exp.id          = obj["id"].toInt();
        exp.company     = obj["company"].toString();
        exp.client      = obj["client"].toString();     // null JSON → ""
        exp.role        = obj["role"].toString();
        exp.location    = obj["location"].toString();
        exp.startDate   = obj["startDate"].toString();
        exp.endDate     = obj["endDate"].toString();    // null JSON → ""
        exp.current     = obj["current"].toBool();
        exp.domain      = obj["domain"].toString();
        exp.description = obj["description"].toString();

        // tasks : tableau de strings
        const QJsonArray tasksArr = obj["tasks"].toArray();
        for (const QJsonValue &t : tasksArr)
            exp.tasks.append(t.toString());

        // technologies : tableau de strings
        const QJsonArray techArr = obj["technologies"].toArray();
        for (const QJsonValue &t : techArr)
            exp.technologies.append(t.toString());

        list.append(exp);
    }

    model->setExperiences(list);
}

// ══════════════════════════════════════════════
//  SKILLS
// ══════════════════════════════════════════════
void DataLoader::loadSkills(const QString      &path,
                            SkillCategoryModel *hardSkills,
                            SoftSkillModel     *softSkills)
{
    QJsonObject root = readJsonObject(path);
    if (root.isEmpty()) return;

    // --- Hard skills : tableau de catégories ---
    QList<SkillCategory> categories;
    const QJsonArray catArray = root["hardSkills"].toArray();

    for (const QJsonValue &catVal : catArray) {
        QJsonObject catObj = catVal.toObject();

        SkillCategory cat;
        cat.category = catObj["category"].toString();

        const QJsonArray itemsArr = catObj["items"].toArray();
        for (const QJsonValue &itemVal : itemsArr) {
            QJsonObject itemObj = itemVal.toObject();
            SkillItem item;
            item.name     = itemObj["name"].toString();
            item.level    = itemObj["level"].toInt();
            item.yearsExp = itemObj["yearsExp"].toInt();
            cat.items.append(item);
        }

        categories.append(cat);
    }
    hardSkills->setCategories(categories);

    // --- Soft skills : tableau simple ---
    QList<SoftSkill> softs;
    const QJsonArray softArray = root["softSkills"].toArray();

    for (const QJsonValue &val : softArray) {
        QJsonObject obj = val.toObject();
        SoftSkill s;
        s.name = obj["name"].toString();
        s.icon = obj["icon"].toString();
        softs.append(s);
    }
    softSkills->setSoftSkills(softs);
}

// ══════════════════════════════════════════════
//  EDUCATION
// ══════════════════════════════════════════════
void DataLoader::loadEducation(const QString &path, EducationModel *model)
{
    QJsonArray array = readJsonArray(path);
    if (array.isEmpty()) return;

    QList<Education> list;
    for (const QJsonValue &val : array) {
        QJsonObject obj = val.toObject();

        Education edu;
        edu.id             = obj["id"].toInt();
        edu.institution    = obj["institution"].toString();
        edu.degree         = obj["degree"].toString();
        edu.specialization = obj["specialization"].toString();
        edu.location       = obj["location"].toString();
        edu.startYear      = obj["startYear"].toInt();
        edu.endYear        = obj["endYear"].toInt();
        edu.level          = obj["level"].toString();

        list.append(edu);
    }

    model->setEducations(list);
}

// ══════════════════════════════════════════════
//  UTILITAIRES
// ══════════════════════════════════════════════

// Lit un fichier JSON et retourne l'objet racine {}
QJsonObject DataLoader::readJsonObject(const QString &path){
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly)){
        emit loadingError("Imposible d'ouvrir : "+path);
        return QJsonObject();
    }

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);

    if(err.error != QJsonParseError::NoError){
        emit loadingError("Json invalide dans : "+path+" : "+err.errorString());
        return QJsonObject();
    }

    return doc.object();
}

// Lit un fichier JSON et retourne le tableau racine []
QJsonArray DataLoader::readJsonArray(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        emit loadingError("Impossible d'ouvrir : " + path);
        return QJsonArray();
    }

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);

    if (err.error != QJsonParseError::NoError) {
        emit loadingError("JSON invalide dans " + path + " : " + err.errorString());
        return QJsonArray();
    }

    return doc.array();
}
