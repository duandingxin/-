#ifndef DATATABLEWIG_H
#define DATATABLEWIG_H

#include <QWidget>
#include "../qcustomplot.h"
#include <customplotWidget/XxwCustomPlot.h>

namespace Ui {
class dataTableWig;
}

class dataTableWig : public QWidget
{
    Q_OBJECT

public:
    explicit dataTableWig(QWidget *parent = nullptr);
    ~dataTableWig();

    /**
     * @brief addGraphData  添加曲线数据到表格中
     * @param graphData
     */
    void addGraphData(XxwCustomPlot *plot, QCPGraph* graphData);

    /**
     * @brief addTracerItems    标记数据点
     * @param x
     * @param y
     */
    void addTracerItems(double x, double y);

    /**
     * @brief setcurWidgetId        设置当前窗口的id
     * @param id                    导航树中节点的id
     */
    void setcurWidgetId(QString id);

    /**
     * @brief getCurWidgetId        获取当前激活窗口的id
     * @return
     */
    QString getCurWidgetId();

    /**
     * @brief ClearTabData          清空当前表格数据
     */
    void ClearTabData();

    /**
     * @brief calculatorUnit            计算单位
     * @param index
     */
    void calculatorUnit(int index);

    void calculatorUnitMS(int index);

    void calculatorUnitUS(int index);

    void calculatorUnitNS(int index);

    /**
     * @brief unitConversionToS 将单位换算成秒
     * @param sourceData 源数据
     * @return 换算成秒后的数据
     */
    double unitConversionToS(double sourceData);
    /**
     * @brief unitConversion 获取单位转换比值
     * @param sourceUnit 源单位（下拉框的索引）
     * @param targetUnit 目的单位（下拉框的索引）
     * @return
     */
    double unitConversion(int sourceUnit,int targetUnit);


private slots:
    /**
     * @brief on_btn_locatorData_clicked    曲线数据范围值定位
     */
    void on_btn_locatorData_clicked();

    /**
     * @brief on_btnClearTracer_clicked     清空定位数据
     */
    void on_btnClearTracer_clicked();

    /**
     * @brief on_tableWidget_itemClicked    点击item触发的槽函数
     * @param item
     */
    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_comboBox_currentIndexChanged(int index);

  //  void on_doubleSpinBox_end_valueChanged(double arg1);



//    void on_doubleSpinBox_start_valueChanged(double arg1);

signals:
    /**
     * @brief sig_SendlocatorData       发送全局的定位数据
     * @param begin                     开始坐标
     * @param end                       结束坐标
     */
    void sig_SendlocatorData(double begin,double end);

    /**
     * @brief sig_ClearlocatorData      清空定位数据
     */
    void sig_ClearlocatorData();

private:
    Ui::dataTableWig *ui;

    QCPGraph * customGraph;         //曲线对象
    XxwCustomPlot *customPlot;      //曲线场景
    QString m_CurrentWindowId;      //当前窗口的id
    int unit;
};

#endif // DATATABLEWIG_H
