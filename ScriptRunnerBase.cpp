#include "ScriptRunnerBase.hpp"


ScriptRunnerBase::ScriptRunnerBase()
{
}

ScriptRunnerBase::~ScriptRunnerBase()
{

}

void ScriptRunnerBase::debug(const QString &value) const
{
    qDebug("%s", qPrintable(value));
}
