#ifndef MAINDIALOGIMPL_H
#define MAINDIALOGIMPL_H

#include <QMainWindow>
#include <QProcess>
#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QString>
#include <QFileInfo>
#include <QCloseEvent>
#include <QMenu>
#include <QClipboard>
#include <QElapsedTimer>
#include <cmath>
#include "ui_mainwindow.h"


class CoreVariables
{
    public:
        bool from_file;
        QString input_file;
        int n_pulses;
        QString E0, r0, tau0, vc, t_inj, Dt_train;
        QString components, layout;
        bool noprop;
        QString p_CO2, p_N2, p_He, percent_13C, percent_18O, T0;
        QString pumping, Vd, D_interel, pump_wl, pump_sigma, pump_fluence;
        QString discharge;
        QString t_pulse_min, t_pulse_max;
        int precision_t, precision_r;
        int component, pulse;
};


class MainWindow : public QMainWindow, public Ui::MainWindowClass
{
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();
        int version;
        QString work_dir;
        QString project_file;
        QString def_dir;
        QString path_to_core, path_to_gnuplot, path_to_7zip;
        QProcess *process;
        bool flag_calculating;
        bool flag_calculation_success;
        bool flag_field_ready_to_save; // can save .co2x file
        bool flag_projectloaded;
        bool flag_plot_modified;
        bool flag_comments_modified;
        bool flag_input_file_error;
        bool noam; // no active medium components
        QElapsedTimer timer;
        CoreVariables Saved, Memorized;
        void LoadProject();
        int FigureMenu();

    private slots:
        void Abort();
        void on_toolButton_input_file_clicked();
        void on_toolButton_layout_clicked();
        void on_toolButton_components_clicked();
        void on_toolButton_discharge_clicked();
        void on_pushButton_new_clicked();
        void on_pushButton_open_clicked();
        void on_pushButton_saveas_clicked();
        void closeEvent(QCloseEvent*);
        void on_label_fig1_customContextMenuRequested();
        void on_label_fig2_customContextMenuRequested();
        void on_label_fig3_customContextMenuRequested();
        void on_label_fig4_customContextMenuRequested();
        void on_label_fig5_customContextMenuRequested();
        void on_label_fig6_customContextMenuRequested();
        void on_label_fig7_customContextMenuRequested();
        void on_label_fig8_customContextMenuRequested();
        void on_label_fig9_customContextMenuRequested();
        void SaveSettings(QString what_to_save); //what_to_save: "all" - input and plot settings; "plot" - plot settings only
        void MemorizeSettings();
        void SaveProject();
        void LoadSettings(QString);
        void NewProject(void);
        void ClearWorkDir(void);
        void Calculate();
        void Plot();
        void Comments();
        void SelectEnergies();
        void ShowFigures();void CopyMultipassData(QString filename);
        void UpdateTerminal();
        void UpdateControls();
        void BeforeProcessStarted();
        void AfterProcessFinished();
        void OnModified();
        void LoadInputPulse();
        int PassNumber(int);
        int DatasetNumber(int pulse_n, int comp_n, int pass_n, QString filename);
        int AmNumber(int);
        bool SaveBeforeClose();
        void BlockSignals(bool block);
};

#endif
