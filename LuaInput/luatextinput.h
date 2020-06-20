#ifndef LUATEXTINPUT_H
#define LUATEXTINPUT_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QTextBlock>
#include <QPainter>

class LineNumberArea;

class LuaTextInput : public QPlainTextEdit
{
    Q_OBJECT

public:
    LuaTextInput(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void sendText();

signals:
    void theText(QString plain_text);

private slots:
   void updateLineNumberAreaWidth(int newBlockCount);
   void highlightCurrentLine();
   void updateLineNumberArea(const QRect &rect, int dy);

private:
    QWidget* lineNumberArea;
};

class LineNumberArea : public QWidget
{

public:
    LineNumberArea(LuaTextInput *editor):QWidget(editor),codeEditor(editor)
    {}

    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(),0);
    }
protected:
    void paintEvent(QPaintEvent *event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }
private:
    LuaTextInput *codeEditor;

};

#endif // LUATEXTINPUT_H
