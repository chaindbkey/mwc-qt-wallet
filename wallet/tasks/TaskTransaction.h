#ifndef MWC_QT_WALLET_TASKTRANSACTION_H
#define MWC_QT_WALLET_TASKTRANSACTION_H

#include "../mwc713task.h"

namespace wallet {

class TaskTransactions : public Mwc713Task {
public:
    const static long TIMEOUT = 1000*60;

    TaskTransactions( MWC713 * wallet713  ) :
            Mwc713Task("Transactions", "txs", wallet713, "") {}

    virtual ~TaskTransactions() override {}

    virtual bool processTask(const QVector<WEvent> & events) override;

    virtual QSet<WALLET_EVENTS> getReadyEvents() override {return QSet<WALLET_EVENTS>{ WALLET_EVENTS::S_READY };}
};



class TaskTransCancel : public Mwc713Task {
public:
    const static long TIMEOUT = 1000*7;

    TaskTransCancel( MWC713 * wallet713, long transId ) :
            Mwc713Task("TaskTransCancel", "cancel --id " + QString::number(transId) , wallet713, ""), transactionId(transId) {}

    virtual ~TaskTransCancel() override {}

    virtual bool processTask(const QVector<WEvent> & events) override;

    virtual QSet<WALLET_EVENTS> getReadyEvents() override {return QSet<WALLET_EVENTS>{ WALLET_EVENTS::S_READY };}
private:
    long transactionId;
    QString proofFileName;
};



class TaskTransExportProof : public Mwc713Task {
public:
    const static long TIMEOUT = 1000*7;

    TaskTransExportProof( MWC713 * wallet713, QString fileName, long transId ) :
            Mwc713Task("TransExportProof", "export-proof --file \"" + fileName + "\" --id " + QString::number(transId) , wallet713, ""), transactionId(transId), proofFileName(fileName) {}

    virtual ~TaskTransExportProof () override {}

    virtual bool processTask(const QVector<WEvent> & events) override;

    virtual QSet<WALLET_EVENTS> getReadyEvents() override {return QSet<WALLET_EVENTS>{ WALLET_EVENTS::S_READY };}
private:
    long transactionId;
    QString proofFileName;
};

class TaskTransVerifyProof : public Mwc713Task {
public:
    const static long TIMEOUT = 1000*7;

    TaskTransVerifyProof( MWC713 * wallet713, QString fileName  ) :
            Mwc713Task("TaskTransVerifyProof", "verify-proof --file \"" + fileName + "\"", wallet713, ""), proofFileName(fileName) {}

    virtual ~TaskTransVerifyProof () override {}

    virtual bool processTask(const QVector<WEvent> & events) override;

    virtual QSet<WALLET_EVENTS> getReadyEvents() override {return QSet<WALLET_EVENTS>{ WALLET_EVENTS::S_READY };}
private:
    QString proofFileName;
};


}

#endif //MWC_QT_WALLET_TASKTRANSACTION_H