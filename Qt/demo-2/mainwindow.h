#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QLabel>
#include <DApplicationHelper>
#include <QVBoxLayout>
#include <DSpinner>
#include <QPushButton>
#include <DSuggestButton>
#include <DMainWindow>

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void keyPressEvent(QKeyEvent *e);
    void closeEvent(QCloseEvent *event);
    void noResolutions();
    void loadDevice();
    void setVendorIcon();

private Q_SLOTS:
    void loadResolutions();
    void onUpdateBtnClicked();
    void onToggleBtnClicked();
    void onRebootBtnClicked();
    void onCancelBtnClicked();
    void onPreInstallProgress(int progress);
    void onThemeChanged(DGuiApplicationHelper::ColorType type);


private:
    int m_usedIndex = 0;
    int m_selectedIndex = 0;

    QWidget *m_centerWidget;
    QVBoxLayout *m_resolutionsLayout;
    QLabel *m_vendorIcon;
    QLabel *m_vendorName;
    QLabel *m_tipsIcon;
    QLabel *m_warningTips;
    QLabel *m_installTips;
    QWidget *m_resolutionsWidget;
    QPushButton *m_toggleButton;
    QPushButton *m_updateButton;
    QPushButton *m_cancelButton;
    QPushButton *m_okButton;

};
