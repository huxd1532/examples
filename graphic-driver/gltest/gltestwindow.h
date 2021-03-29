#ifndef GLTESTWINDOW_H
#define GLTESTWINDOW_H

#include "gltestwidget.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>


class GLTestWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GLTestWindow(QWidget *parent = nullptr);

private slots:
    void onAccept();

    void onCancel();

private:
    bool m_exit_gltest;
    GLTestWidget *m_glTestWidget;
    QLabel *m_tipsLabel;
    QPushButton *m_acceptBtn;
    QPushButton *m_cancelBtn;
};

#endif
