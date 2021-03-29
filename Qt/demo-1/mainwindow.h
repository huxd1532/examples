#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QPlainTextEdit>
#include <QPushButton>


class MainWindow : public QWidget
{
    Q_OBJECT
private:
    QCheckBox   *chkBoxUnder;
    QCheckBox   *chkBoxItalic;
    QCheckBox   *chkBoxBold;
    QRadioButton    *rBtnBlack;
    QRadioButton    *rBtnRed;
    QRadioButton    *rBtnBlue;
    QPlainTextEdit  *txtEdit;
    QPushButton     *btnOK;
    QPushButton     *btnCancel;
    QPushButton     *btnClose;
    void    iniUI();//UI 创建与初始化
    void    iniSignalSlots();//初始化信号与槽的链接
private slots:
    void on_chkBoxUnder(bool checked); //Underline 的clicked(bool)信号的槽函数
    void on_chkBoxItalic(bool checked);//Italic 的clicked(bool)信号的槽函数
    void on_chkBoxBold(bool checked); //Bold 的clicked(bool)信号的槽函数
    void setTextFontColor(); //设置字体颜色
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
