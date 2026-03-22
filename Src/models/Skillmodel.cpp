#include "SkillModel.hpp"

// ══════════════════════════════════════════════
//  SkillCategoryModel
// ══════════════════════════════════════════════

SkillCategoryModel::SkillCategoryModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int SkillCategoryModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_categories.size();
}

QVariant SkillCategoryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_categories.size())
        return QVariant();

    const SkillCategory &cat = m_categories.at(index.row());

    switch (role) {
    case CategoryNameRole: return cat.category;
    case ItemsRole:        return itemsToVariant(cat.items);
    default:               return QVariant();
    }
}

QHash<int, QByteArray> SkillCategoryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CategoryNameRole] = "categoryName";
    roles[ItemsRole]        = "items";
    return roles;
}

void SkillCategoryModel::setCategories(const QList<SkillCategory> &categories)
{
    beginResetModel();
    m_categories = categories;
    endResetModel();
}

// ─────────────────────────────────────────────
// itemsToVariant — convertit les SkillItem C++
// en QVariantList pour QML
//
// En QML chaque item sera accessible ainsi :
//   modelData.name      → "C++"
//   modelData.level     → 95
//   modelData.yearsExp  → 5
// ─────────────────────────────────────────────
QVariantList SkillCategoryModel::itemsToVariant(const QList<SkillItem> &items) const
{
    QVariantList result;
    for (const SkillItem &item : items) {
        QVariantMap map;
        map["name"]     = item.name;
        map["level"]    = item.level;
        map["yearsExp"] = item.yearsExp;
        result.append(map);
    }
    return result;
}

// ══════════════════════════════════════════════
//  SoftSkillModel
// ══════════════════════════════════════════════

SoftSkillModel::SoftSkillModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int SoftSkillModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_softSkills.size();
}

QVariant SoftSkillModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_softSkills.size())
        return QVariant();

    const SoftSkill &skill = m_softSkills.at(index.row());

    switch (role) {
    case NameRole: return skill.name;
    case IconRole: return skill.icon;
    default:       return QVariant();
    }
}

QHash<int, QByteArray> SoftSkillModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    return roles;
}

void SoftSkillModel::setSoftSkills(const QList<SoftSkill> &softSkills)
{
    beginResetModel();
    m_softSkills = softSkills;
    endResetModel();
}
