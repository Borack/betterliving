#ifndef SCRIPTRUNNERBASE_HPP
#define SCRIPTRUNNERBASE_HPP

#include <QObject>
#include <QByteArray>
#include <QWebPage>

class ScriptRunnerBase : public QObject
{
      Q_OBJECT
   public:
      ScriptRunnerBase(QWebPage* page);
      virtual ~ScriptRunnerBase();

   public slots:
      virtual void debug(const QString &value) const;

   protected:
      QWebPage * m_webPage;
      virtual QByteArray loadScript(const QString& scriptName) {}

   signals:
      virtual void statusUpdate(const QString&);
      virtual void halt(const QString&);

};

#endif // SCRIPTRUNNERBASE_HPP
