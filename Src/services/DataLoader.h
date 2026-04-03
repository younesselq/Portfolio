#pragma once

#include <QObject>
#include <QString>

#include "../models/ProfileModel.h"
#include "../models/ExperienceModel.h"
#include "../models/SkillModel.h"
#include "../models/EducationModel.h"

class DataLoader : public QObject
{
    Q_OBJECT

public:
    explicit DataLoader(QObject *parent = nullptr);

    // Point d'entrée unique — appelé une fois dans main.cpp
    // basePath = chemin vers le dossier resources/data/
    void loadAll(const QString     &basePath,
                 ProfileModel      *profile,
                 ExperienceModel   *experiences,
                 SkillCategoryModel *hardSkills,
                 SoftSkillModel    *softSkills,
                 EducationModel    *education);

signals:
    void loadingFinished();
    void loadingError(const QString &message);

private:
    // Un parseur par fichier JSON
    void loadProfile    (const QString &path, ProfileModel       *model);
    void loadExperiences(const QString &path, ExperienceModel    *model);
    void loadSkills     (const QString &path,
                    SkillCategoryModel *hardSkills,
                    SoftSkillModel     *softSkills);
    void loadEducation  (const QString &path, EducationModel     *model);

    // Utilitaire : lit un fichier et retourne le QJsonObject racine
    // Retourne un objet vide et émet loadingError si le fichier est invalide
    QJsonObject readJsonObject(const QString &path);
    QJsonArray  readJsonArray (const QString &path);
};
