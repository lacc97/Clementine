#ifndef DROPBOXAUTHENTICATOR_H
#define DROPBOXAUTHENTICATOR_H

#include <QObject>
#include <QTcpServer>

class NetworkAccessManager;
class QNetworkReply;

class DropboxAuthenticator : public QObject {
  Q_OBJECT
 public:
  explicit DropboxAuthenticator(QObject* parent = 0);
  void StartAuthorisation(const QString& email);

 private slots:
  void RequestTokenFinished(QNetworkReply* reply);
  void RedirectArrived(QTcpSocket* socket, QByteArray buffer);
  void NewConnection();
  void RequestAccessTokenFinished(QNetworkReply* reply);
  void RequestAccountInformationFinished(QNetworkReply* reply);

 private:
  void Authorise();
  void RequestAccessToken();
  QByteArray GenerateAuthorisationHeader();
  void RequestAccountInformation();

 private:
  NetworkAccessManager* network_;
  QTcpServer server_;

  // Temporary access token used for first authentication flow.
  QString token_;
  QString secret_;

  // User's Dropbox uid.
  QString uid_;

  // Permanent OAuth access tokens.
  QString access_token_;
  QString access_token_secret_;
};

#endif  // DROPBOXAUTHENTICATOR_H
