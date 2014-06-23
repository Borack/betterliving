#include "ScriptRunnerBase.hpp"

ScriptRunnerBase::ScriptRunnerBase(QWebPage *page)
   : m_webPage(page)
{

}

ScriptRunnerBase::~ScriptRunnerBase()
{

}

void ScriptRunnerBase::debug(const QString &value) const
{
    qDebug("%s", qPrintable(value));
}
