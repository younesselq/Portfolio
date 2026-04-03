#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QString>
#include <QVariantList>
#include <QtQml/qqml.h>

// ─── Structures ───────────────────────────────

struct SkillItem {
    QString name;
    int     level;
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

// ─── SkillCategoryModel ───────────────────────

class SkillCategoryModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    enum Roles {
        CategoryNameRole = Qt::UserRole + 1,
        ItemsRole
    };
    Q_ENUM(Roles)

    static SkillCategoryModel *create(QQmlEngine *, QJSEngine *)
    {
        return instance();
    }

    static SkillCategoryModel *instance()
    {
        static SkillCategoryModel inst;
        return &inst;
    }

    int      rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setCategories(const QList<SkillCategory> &categories);

private:
    explicit SkillCategoryModel(QObject *parent = nullptr)
        : QAbstractListModel(parent) {}

    QVariantList itemsToVariant(const QList<SkillItem> &items) const;

    QList<SkillCategory> m_categories;
};

// ─── SoftSkillModel ───────────────────────────

class SoftSkillModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        IconRole
    };
    Q_ENUM(Roles)

    static SoftSkillModel *create(QQmlEngine *, QJSEngine *)
    {
        return instance();
    }

    static SoftSkillModel *instance()
    {
        static SoftSkillModel inst;
        return &inst;
    }

    int      rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setSoftSkills(const QList<SoftSkill> &softSkills);

private:
    explicit SoftSkillModel(QObject *parent = nullptr)
        : QAbstractListModel(parent) {}

    QList<SoftSkill> m_softSkills;
};
