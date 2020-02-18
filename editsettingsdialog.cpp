#include "editsettingsdialog.h"

EditSettingsDialog::EditSettingsDialog(SerialExchange* serial, QWidget *parent):
     QDialog(parent), m_serial(serial)
{
    m_serial = serial;

    buttonBox = new QDialogButtonBox(this);
    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Cancel);

    connect(buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(setSettings()));
    connect(buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(cancel()));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(createSettingsDataGroup());
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle("Изменить установки");
}

EditSettingsDialog::~EditSettingsDialog(){}

void EditSettingsDialog::setSettings(){
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setAttribute( Qt::WA_DeleteOnClose, true );
    msgBox->setText("Вы собираетесь изменить текущие настройки.");
    msgBox->setIcon(QMessageBox::Warning);
    msgBox->setInformativeText("Вы уверены, что хотите выполнить это действие?");
    msgBox->addButton("Да", QMessageBox::AcceptRole);
    msgBox->addButton("Отмена", QMessageBox::RejectRole);
    msgBox->setWindowTitle("Предупреждение");

    if(msgBox->exec() == QMessageBox::AcceptRole){
        m_serial->setInVoltageCorrection( inVoltageCorrection->value());
        m_serial->setOutVoltageCorrection( outVoltageCorrection->value());
        m_serial->setInCurrentCorrection( inCurrentCorrection->value());
        m_serial->setOutCurrentCorrection( outCurrentCorrection->value());
        m_serial->setTurnOnTime( turnOnTime->value());
        m_serial->setVoltageSt1( voltageSt1->value());
        m_serial->setVoltageSt2( voltageSt2->value());
        m_serial->setMinInVoltageOff( minInVoltageOff->value());
        m_serial->setMinInVoltageOffTime( minInVoltageOffTime->value());
        m_serial->setMaxInVoltageOff( maxInVoltageOff->value());
        m_serial->setMaxInVoltageOffTime( maxInVoltageOffTime->value());
        m_serial->setMinOutVoltageOff( minOutVoltageOff->value());
        m_serial->setMinOutVoltageOffTime( minOutVoltageOffTime->value());
        m_serial->setMaxOutVoltageOff( maxOutVoltageOff->value());
        m_serial->setMaxOutVoltageOffTime( maxOutVoltageOffTime->value());
        m_serial->setInCurrentOff( inCurrentOff->value());
        m_serial->setInCurrentOffTime( inCurrentOffTime->value());
        m_serial->setOutCurrentOff( outCurrentOff->value());
        m_serial->setOutCurrentOffTime( outCurrentOffTime->value());
        m_serial->setTemperatureOff( temperatureOff->value());
        m_serial->setIndicationMode( indicationMode->value());

        m_serial->setSettingData();
        m_serial->getSettingData();
        hide();
    }
}
void EditSettingsDialog::cancel(){
    hide();
}

QGroupBox *EditSettingsDialog::createSettingsDataGroup(){
    QGroupBox *groupBox = new QGroupBox("Текущие значения установок", this);

    QLabel *inVoltageCorrectionLabel = new QLabel("Коррекция вход. напряжения: ");
    inVoltageCorrection = new QSpinBox(this);
    inVoltageCorrection->setSuffix("В");
    inVoltageCorrection->setRange(-10, 10);
    inVoltageCorrection->setValue(m_serial->getInVoltageCorrection());

    QLabel *outVoltageCorrectionLabel = new QLabel("Коррекция выход. напряжения: ");
    outVoltageCorrection = new QSpinBox(this);
    outVoltageCorrection->setSuffix("В");
    outVoltageCorrection->setRange(-10, 10);
    outVoltageCorrection->setValue(m_serial->getOutVoltageCorrection());


    QLabel *inCurrentCorrectionLabel = new QLabel("Коррекция вход. тока: ");
    inCurrentCorrection = new QSpinBox(this);
    inCurrentCorrection->setSuffix("%");
    inCurrentCorrection->setRange(-10, 10);
    inCurrentCorrection->setValue(m_serial->getInCurrentCorrection());

    QLabel *outCurrentCorrectionLabel = new QLabel("Коррекция выход. тока: ");
    outCurrentCorrection = new QSpinBox(this);
    outCurrentCorrection->setSuffix("%");
    outCurrentCorrection->setRange(-10, 10);
    outCurrentCorrection->setValue(m_serial->getOutCurrentCorrection());

    QLabel *turnOnTimeLabel = new QLabel("Время на включение: ");
    turnOnTime = new QSpinBox(this);
    turnOnTime->setSuffix("c");
    turnOnTime->setRange(1, 999);
    turnOnTime->setValue(m_serial->getTurnOnTime());

    QLabel *voltageSt1Label = new QLabel("Напряжение стабил. 1: ");
    voltageSt1 = new QSpinBox(this);
    voltageSt1->setSuffix("В");
    voltageSt1->setRange(200, 235);
    voltageSt1->setValue(m_serial->getVoltageSt1());

    QLabel *voltageSt2Label = new QLabel("Напряжение стабил. 2: ");
    voltageSt2 = new QSpinBox(this);
    voltageSt2->setSuffix("В");
    voltageSt2->setRange(210, 245);
    voltageSt2->setValue(m_serial->getVoltageSt2());

    QLabel *minInVoltageOffLabel = new QLabel("Мин. вход. напряжение отключения: ");
    minInVoltageOff = new QSpinBox(this);
    minInVoltageOff->setSuffix("В");
    minInVoltageOff->setRange(70, 180);
    minInVoltageOff->setValue(m_serial->getMinInVoltageOff());

    QLabel *minInVoltageOffTimeLabel = new QLabel("Время на отключение: ");
    minInVoltageOffTime = new QSpinBox(this);
    minInVoltageOffTime->setSuffix("c");
    minInVoltageOffTime->setRange(1, 250);
    minInVoltageOffTime->setValue(m_serial->getMinInVoltageOffTime());

    QLabel *maxInVoltageOffLabel = new QLabel("Макс. вход. напряжение отключения: ");
    maxInVoltageOff = new QSpinBox(this);
    maxInVoltageOff->setSuffix("В");
    maxInVoltageOff->setRange(240, 360);
    maxInVoltageOff->setValue(m_serial->getMaxInVoltageOff());

    QLabel *maxInVoltageOffTimeLabel = new QLabel("Время на отключение: ");
    maxInVoltageOffTime = new QSpinBox(this);
    maxInVoltageOffTime->setSuffix("c");
    maxInVoltageOffTime->setRange(1, 250);
    maxInVoltageOffTime->setValue(m_serial->getMaxInVoltageOffTime());

    QLabel *minOutVoltageOffLabel = new QLabel("Мин. выход. напряжение отключения: ");
    minOutVoltageOff = new QSpinBox(this);
    minOutVoltageOff->setSuffix("В");
    minOutVoltageOff->setRange(90, 230);
    minOutVoltageOff->setValue(m_serial->getMinOutVoltageOff());

    QLabel *minOutVoltageOffTimeLabel = new QLabel("Время на отключение: ");
    minOutVoltageOffTime = new QSpinBox(this);
    minOutVoltageOffTime->setSuffix("c");
    minOutVoltageOffTime->setRange(1, 250);
    minOutVoltageOffTime->setValue(m_serial->getMinOutVoltageOffTime());

    QLabel *maxOutVoltageOffLabel = new QLabel("Макс. выход. напряжение отключения: ");
    maxOutVoltageOff = new QSpinBox(this);
    maxOutVoltageOff->setSuffix("В");
    maxOutVoltageOff->setRange(220, 250);
    maxOutVoltageOff->setValue(m_serial->getMaxOutVoltageOff());

    QLabel *maxOutVoltageOffTimeLabel = new QLabel("Время на отключение:");
    maxOutVoltageOffTime = new QSpinBox(this);
    maxOutVoltageOffTime->setSuffix("c");
    maxOutVoltageOffTime->setRange(1, 250);
    maxOutVoltageOffTime->setValue(m_serial->getMaxOutVoltageOffTime());

    QLabel *inCurrentOffLabel = new QLabel("Вход. ток отключения: ");
    inCurrentOff = new QSpinBox(this);
    inCurrentOff->setSuffix("%");
    inCurrentOff->setRange(40, 120);
    inCurrentOff->setValue(m_serial->getInCurrentOff());

    QLabel *inCurrentOffTimeLabel = new QLabel("Время на отключение: ");
    inCurrentOffTime = new QSpinBox(this);
    inCurrentOffTime->setSuffix("c");
    inCurrentOffTime->setRange(1, 200);
    inCurrentOffTime->setValue(m_serial->getInCurrentOffTime());

    QLabel *outCurrentOffLabel = new QLabel("Выход. ток отключения: ");
    outCurrentOff = new QSpinBox(this);
    outCurrentOff->setSuffix("%");
    outCurrentOff->setRange(40, 120);
    outCurrentOff->setValue(m_serial->getOutCurrentOff());

    QLabel *outCurrentOffTimeLabel = new QLabel("Время на отключение: ");
    outCurrentOffTime = new QSpinBox(this);
    outCurrentOffTime->setSuffix("c");
    outCurrentOffTime->setRange(1, 200);
    outCurrentOffTime->setValue(m_serial->getOutCurrentOffTime());

    QLabel *temperatureOffLabel = new QLabel("Температура отключения: ");
    temperatureOff = new QSpinBox(this);
    temperatureOff->setSuffix("°С");
    temperatureOff->setRange(60, 100);
    temperatureOff->setValue(m_serial->getTemperatureOff());

    QLabel *indicationModeLabel = new QLabel("Режим индикации:");
    indicationMode = new QSpinBox(this);
    indicationMode->setRange(0, 44);
    indicationMode->setValue(m_serial->getIndicationMode());

    QGridLayout *gbox = new QGridLayout(this);
    gbox->addWidget(inVoltageCorrectionLabel, 0, 0);
    gbox->addWidget(outVoltageCorrectionLabel, 0, 1);
    gbox->addWidget(inVoltageCorrection, 1, 0);
    gbox->addWidget(outVoltageCorrection, 1, 1);
    gbox->addWidget(inCurrentCorrectionLabel, 2, 0);
    gbox->addWidget(outCurrentCorrectionLabel, 2, 1);
    gbox->addWidget(inCurrentCorrection, 3, 0);
    gbox->addWidget(outCurrentCorrection, 3, 1);
    gbox->addWidget(turnOnTimeLabel, 4, 0);
    gbox->addWidget(turnOnTime, 5, 0);
    gbox->addWidget(voltageSt1Label, 6, 0);
    gbox->addWidget(voltageSt2Label, 6, 1);
    gbox->addWidget(voltageSt1, 7, 0);
    gbox->addWidget(voltageSt2, 7, 1);
    gbox->addWidget(minInVoltageOffLabel, 8, 0);
    gbox->addWidget(minInVoltageOffTimeLabel, 8, 1);
    gbox->addWidget(minInVoltageOff, 9, 0);
    gbox->addWidget(minInVoltageOffTime, 9, 1);
    gbox->addWidget(maxInVoltageOffLabel, 10, 0);
    gbox->addWidget(maxInVoltageOffTimeLabel, 10, 1);
    gbox->addWidget(maxInVoltageOff, 11, 0);
    gbox->addWidget(maxInVoltageOffTime, 11, 1);
    gbox->addWidget(minOutVoltageOffLabel, 12, 0);
    gbox->addWidget(minOutVoltageOffTimeLabel, 12, 1);
    gbox->addWidget(minOutVoltageOff, 13, 0);
    gbox->addWidget(minOutVoltageOffTime, 13, 1);
    gbox->addWidget(maxOutVoltageOffLabel, 14, 0);
    gbox->addWidget(maxOutVoltageOffTimeLabel, 14, 1);
    gbox->addWidget(maxOutVoltageOff, 15, 0);
    gbox->addWidget(maxOutVoltageOffTime, 15, 1);
    gbox->addWidget(inCurrentOffLabel, 16, 0);
    gbox->addWidget(inCurrentOffTimeLabel, 16, 1);
    gbox->addWidget(inCurrentOff, 17, 0);
    gbox->addWidget(inCurrentOffTime, 17, 1);
    gbox->addWidget(outCurrentOffLabel, 18, 0);
    gbox->addWidget(outCurrentOffTimeLabel, 18, 1);
    gbox->addWidget(outCurrentOff, 19, 0);
    gbox->addWidget(outCurrentOffTime, 19, 1);
    gbox->addWidget(temperatureOffLabel, 20, 0);
    gbox->addWidget(indicationModeLabel, 20, 1);
    gbox->addWidget(temperatureOff, 21, 0);
    gbox->addWidget(indicationMode, 21, 1);

    groupBox->setLayout(gbox);
    return groupBox;
}
