#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QMainWindow>
#include <vector>
#include <QSortFilterProxyModel>

class RecordsManager;
class CSVReader;
class TreeModel;
class CustomSort;
class PieChartWidget;
class QListWidget;
class QTreeView;
class QCustomPlot;
class QPrinter;
class QPainter;
class state;
class modifysort;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
    QString load_file();

    void on_pres_load_file_clicked();
    void on_pub_load_file_clicked();
    void on_fund_load_file_clicked();
    void on_teach_load_file_clicked();

    void on_teach_new_sort_clicked();
    void on_pub_new_sort_clicked();
    void on_pres_new_sort_clicked();
    void on_fund_new_sort_clicked();

    void on_teach_modify_sort_clicked();
    void on_pub_modify_sort_clicked();
    void on_pres_modify_sort_clicked();
    void on_fund_modify_sort_clicked();

    void on_actionLoad_file_triggered();

    void on_FromDate_dateChanged(const QDate &date);
    void on_ToDate_dateChanged(const QDate &date);

    void refresh(int tabIndex);

    void on_teach_sort_currentIndexChanged(int index);
    void on_pub_sort_currentIndexChanged(int index);
    void on_pres_sort_currentIndexChanged(int index);
    void on_fund_sort_currentIndexChanged(int index);

    void on_teach_delete_sort_clicked();
    void on_pub_delete_sort_clicked();
    void on_pres_delete_sort_clicked();
    void on_fund_delete_sort_clicked();

    void on_teach_pie_button_toggled();
    void on_teach_bar_button_toggled();
    void on_teach_line_button_toggled();
    void on_teach_scatter_button_toggled();

    void on_pub_pie_button_toggled();
    void on_pub_bar_button_toggled();
    void on_pub_line_button_toggled();
    void on_pub_scatter_button_toggled();

    void on_pres_pie_button_toggled();
    void on_pres_bar_button_toggled();
    void on_pres_line_button_toggled();
    void on_pres_scatter_button_toggled();

    void on_fund_pie_button_toggled();
    void on_fund_bar_button_toggled();
    void on_fund_line_button_toggled();
    void on_fund_scatter_button_toggled();

    void on_teachTreeView_clicked(const QModelIndex &index);
    void on_pubTreeView_clicked(const QModelIndex &index);
    void on_presTreeView_clicked(const QModelIndex &index);
    void on_fundTreeView_clicked(const QModelIndex &index);

    void on_categoryTab_currentChanged();

    void on_teach_filter_from_textChanged();
    void on_teach_filter_to_textChanged();
    void on_pub_filter_from_textChanged();
    void on_pub_filter_to_textChanged();
    void on_pres_filter_from_textChanged();
    void on_pres_filter_to_textChanged();
    void on_fund_filter_from_textChanged();
    void on_fund_filter_to_textChanged();

    void on_teachPrintButton_clicked();

    void on_fundPrintButton_clicked();

    void on_presPrintButton_clicked();

    void on_pubPrintButton_clicked();

    void on_teachExportButton_clicked();

    void on_fundExportButton_clicked();

    void on_presExportButton_clicked();

    void on_pubExportButton_clicked();

    void on_pub_search_clicked();
    void on_pres_search_clicked();
    void on_fund_search_clicked();
    void on_teach_search_clicked();

private:
    static std::vector<std::string> GRANTS_MANFIELDS, PRES_MANFIELDS, PUBS_MANFIELDS, TEACH_MANFIELDS;

    struct field_error;

    Ui::MainWindow* ui;
    QPrinter* printer;

    QList<QStringList> allTeachOrders, allPubOrders, allPresOrders, allFundOrders;
    QString teachPath, pubPath, presPath, fundPath;
    TreeModel *fundTree, *presTree, *pubTree, *teachTree;
    RecordsManager *funddb, *presdb, *pubdb, *teachdb;
    std::vector<std::vector<std::string>> fundData, presData, pubData, teachData;

    std::vector<std::string> teachSortOrder, pubSortOrder, presSortOrder, fundSortOrder;
    TreeModel* currentTree;
    RecordsManager* currentdb;
    QTreeView* currentView;
    QString teachClickedName, pubClickedName, presClickedName, fundClickedName;

    QList<bool> dateChanged;

    std::vector<std::string> getParentsList(QModelIndex &index);
    char getFilterStartChar(int type);
    char getFilterEndChar(int type);

    int yearStart, yearEnd;

    QSortFilterProxyModel *proxyModel;

    int checkFile(int index, QString filePath);
    //std::vector<std::string> getSelectedSortOrder(int tabIndex);
    void createDefaultSortOrder(int tabIndex);
    void makeTree(int tabIndex);

    void setupPieChart(PieChartWidget *pieChart, QListWidget *pieListWidget, std::vector<std::pair<std::string, double> > pieChartList);
    void setupBarChart(QCustomPlot *barChart, std::vector<std::pair<std::string, double> > barChartList);
    void setupLineChart(QCustomPlot *customPlot, std::vector<std::pair<std::string, double> > lineChartList);
    void setupScatterChart(QCustomPlot *customPlot, std::vector<std::pair<std::string, double> > scatterChartList);

    bool handle_field_errors(std::vector<std::vector<std::string>*>& errors,
                             std::vector<std::string>& headers,
                             std::vector<std::string>& mandatory);

    bool load_fund(QString path, bool multi_file = false);
    bool load_pub(QString path, bool multi_file = false);
    bool load_teach(QString path, bool multi_file = false);
    bool load_pres(QString path, bool multi_file = false);

    void serializeFundScreen(QString path);
    void serializePubcreen(QString path);
    void serializeTeachScreen(QString path);
    void serializePresScreen(QString path);

    void loadSerializeFundScreen();
    void loadSerializePubScreen();
    void loadSerializeTeachScreen();
    void loadSerializePresScreen();
    bool fileExists(QString path);
    bool m_flag =0;
    QString filePath;
};

#endif // MAINWINDOW_H
