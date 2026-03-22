#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QString>
#include <QVariantList>

// ─────────────────────────────────────────────
// Structures de données (miroir du JSON)
// ─────────────────────────────────────────────

struct SkillItem {
    QString name;
    int     level;    // 0-100 → utilisé pour les barres de progression QML
    int     yearsExp;
};

struct SkillCategory {
    QString          category;
    QList<SkillItem> items;
};

struct SoftSkill {
    QString name;
    QString icon;
};

// ─────────────────────────────────────────────
// SkillCategoryModel — expose la liste des
// catégories de hard skills dans un ListView QML
// Chaque row = une catégorie avec ses items
// ─────────────────────────────────────────────
class SkillCategoryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        CategoryNameRole = Qt::UserRole + 1,
        ItemsRole           // QVariantList de SkillItem → itérable en QML
    };
    Q_ENUM(Roles)

    explicit SkillCategoryModel(QObject *parent = nullptr);

    int     rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setCategories(const QList<SkillCategory> &categories);

private:
    QList<SkillCategory> m_categories;

    // Convertit QList<SkillItem> → QVariantList
    // pour que QML puisse itérer les items avec un Repeater
    QVariantList itemsToVariant(const QList<SkillItem> &items) const;
};

// ─────────────────────────────────────────────
// SoftSkillModel — expose la liste des soft
// skills (structure plus simple, pas de catégorie)
// ─────────────────────────────────────────────
class SoftSkillModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        IconRole
    };
    Q_ENUM(Roles)

    explicit SoftSkillModel(QObject *parent = nullptr);

    int      rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setSoftSkills(const QList<SoftSkill> &softSkills);

private:
    QList<SoftSkill> m_softSkills;
};
