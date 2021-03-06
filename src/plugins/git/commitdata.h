/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef COMMITDATA_H
#define COMMITDATA_H

#include <QStringList>
#include <QPair>

QT_BEGIN_NAMESPACE
class QDebug;
QT_END_NAMESPACE

namespace Git {
namespace Internal {

// Read-only
struct GitSubmitEditorPanelInfo
{
    void clear();
    QString repository;
    QString description;
    QString branch;
};

QDebug operator<<(QDebug d, const GitSubmitEditorPanelInfo &);

struct GitSubmitEditorPanelData
{
    void clear();
    // Format as "John Doe <jdoe@foobar.com>"
    QString authorString() const;

    QString author;
    QString email;
    bool bypassHooks;
};

QDebug operator<<(QDebug d, const GitSubmitEditorPanelData &);

class CommitData
{
public:
    enum FileState {
        UntrackedFile = 0,

        StagedFile   = 0x01,
        ModifiedFile = 0x02,
        AddedFile    = 0x04,
        DeletedFile  = 0x08,
        RenamedFile  = 0x10,
        CopiedFile   = 0x20,
        UpdatedFile  = 0x40,

        ModifiedStagedFile = StagedFile | ModifiedFile,
        AddedStagedFile = StagedFile | AddedFile,
        DeletedStagedFile = StagedFile | DeletedFile,
        RenamedStagedFile = StagedFile | RenamedFile,
        CopiedStagedFile = StagedFile | CopiedFile,
        UpdatedStagedFile = StagedFile | UpdatedFile,

        AllStates = UpdatedFile | CopiedFile | RenamedFile | DeletedFile | AddedFile | ModifiedFile | StagedFile,
        UnknownFileState
    };

    // A pair of state string/file name ('modified', 'file.cpp').
    typedef QPair<FileState, QString> StateFilePair;

    void clear();
    // Parse the files and the branch of panelInfo
    // from a git status output
    bool parseFilesFromStatus(const QString &output);

    // Convenience to retrieve the file names from
    // the specification list. Optionally filter for a certain state
    QStringList filterFiles(const FileState &state = AllStates) const;

    static QString stateDisplayName(const FileState &state);

    QString amendSHA1;
    QString commitEncoding;
    GitSubmitEditorPanelInfo panelInfo;
    GitSubmitEditorPanelData panelData;

    QList<StateFilePair> files;
};

} // namespace Internal
} // namespace Git

#endif // COMMITDATA_H
