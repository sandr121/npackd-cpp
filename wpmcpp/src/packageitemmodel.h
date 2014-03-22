#ifndef PACKAGEITEMMODEL_H
#define PACKAGEITEMMODEL_H

#include <QAbstractTableModel>
#include <QCache>
#include <QBrush>

#include "package.h"
#include "version.h"

/**
 * @brief shows packages
 */
class PackageItemModel: public QAbstractTableModel
{
    QBrush obsoleteBrush;

    QList<Package*> packages;

    class Info {
    public:
        QString avail;
        QString installed;
        bool up2date;
    };

    mutable QCache<QString, Info> cache;

    Info *createInfo(const QString &package) const;
public:
    /**
     * @param [ownership:this] packages list of packages
     */
    PackageItemModel(const QList<Package*> packages);

    ~PackageItemModel();

    int rowCount(const QModelIndex &parent) const;

    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    /**
     * @brief changes the list of packages
     * @param packages [ownership:this] list of packages
     */
    void setPackages(const QList<Package*> packages);

    /**
     * @brief should be called if an icon has changed
     * @param url URL of the icon
     */
    void iconUpdated(const QString& url);

    /**
     * @brief should be called if the "installed" status of a package version
     *     has changed
     * @param package full package name
     * @param version version number
     */
    void installedStatusChanged(const QString &package, const Version &version);

    /**
     * @brief clears the cache
     */
    void clearCache();
};

#endif // PACKAGEITEMMODEL_H