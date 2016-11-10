/*Author:Jing Li,Yang Bai

 Source file of class"createassignmententry",
 if name theme date or assignment changed,
return the signal that they has changed.



*/
#include "createassignmententry.h"

createassignmententry::createassignmententry(QObject *parent) : QObject(parent),m_expirationdate(QDateTime::currentDateTime())
{

}

QString createassignmententry::name() const
{
    return m_name;
}

void createassignmententry::setName(const QString &name)
{
    if( m_name!=name){
        m_name=name;
        emit nameChanged();
    }
    m_name = name;
}

QString createassignmententry::theme() const
{
    return m_theme;
}

void createassignmententry::setTheme(const QString &theme)
{
    if(m_theme!=theme){
        m_theme=theme;
        emit themeChanged();
    }
}

QDateTime createassignmententry::expirationdate()
{
    return m_expirationdate;
}

void createassignmententry::setExpirationdate(const QDateTime &expirationdate)
{
    if(m_expirationdate!=expirationdate){
    m_expirationdate = expirationdate;
    emit expirationdateChanged();
    }
}

QString createassignmententry::assignment() const
{
    return m_assignment;
}

void createassignmententry::setAssignment(const QString &assignment)
{
    if(m_assignment!=assignment){
        m_assignment=assignment;
        emit assignmentChanged();
    }
}
