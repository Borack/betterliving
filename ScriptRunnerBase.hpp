#ifndef SCRIPTRUNNERBASE_HPP
#define SCRIPTRUNNERBASE_HPP

#include <QObject>
#include <QByteArray>

class ScriptRunnerBase : public QObject
{
      Q_OBJECT
   public:
      ScriptRunnerBase();
      virtual ~ScriptRunnerBase();

   public slots:
      virtual void debug(const QString &value) const;

   protected:
      virtual QByteArray loadScript(const QString& scriptName) {}

   signals:
      virtual void statusUpdate(const QString&);
      virtual void halt(const QString&);

};

#endif // SCRIPTRUNNERBASE_HPP
