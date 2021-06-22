#ifndef SYNHIGHLIGTERBASE_H
#define SYNHIGHLIGTERBASE_H

#include <QColor>
#include <QObject>
#include <memory>
#include <QMap>
#include <QSet>
#include <QVector>
#include <QVector>
#include "../Types.h"

typedef struct {
    int state;
    int spaceState;
} SynRangeState;

typedef int SynTokenKind;

enum class SynHighlighterTokenType {
    Default, Space, Comment,
    PreprocessDirective, String, StringEscapeSequence,
    Identifier, Symbol,
    Character, Keyword, Number};

enum class SynHighlighterClass {
    Composition,
    CppHighlighter,
};

enum class SynHighlighterLanguage {
    Cpp
};

class SynHighlighterAttribute {
public:
    explicit SynHighlighterAttribute(const QString& name);

    QString name() const;
    void setName(const QString &name);

    SynFontStyles styles() const;
    void setStyles(const SynFontStyles &styles);

    QColor foreground() const;
    void setForeground(const QColor &color);

    QColor background() const;
    void setBackground(const QColor &background);

private:
    QColor mForeground;
    QColor mBackground;
    QString mName;
    SynFontStyles mStyles;
};

typedef std::shared_ptr<SynHighlighterAttribute> PSynHighlighterAttribute;
using SynHighlighterAttributeList = QVector<PSynHighlighterAttribute>;

class SynHighlighter {
public:
    explicit SynHighlighter();

    const QMap<QString, PSynHighlighterAttribute>& attributes() const;

    const QSet<QChar>& wordBreakChars() const;



    PSynHighlighterAttribute commentAttribute() const;

    PSynHighlighterAttribute identifierAttribute() const;

    PSynHighlighterAttribute keywordAttribute() const;

    PSynHighlighterAttribute stringAttribute() const;

    PSynHighlighterAttribute whitespaceAttribute() const;

    PSynHighlighterAttribute symbolAttribute() const;

    virtual bool isIdentChar(const QChar& ch) const;

    virtual SynHighlighterClass getClass() const = 0;
    virtual QString getName() const = 0;

    virtual bool getTokenFinished() const = 0;
    virtual bool isLastLineCommentNotFinished(int state) const = 0;
    virtual bool isLastLineStringNotFinished(int state) const = 0;
    virtual bool eol() const = 0;
    virtual SynRangeState getRangeState() const = 0;
    virtual int getBraceLevel() const;
    virtual int getBracketLevel() const;
    virtual int getParenthesisLevel() const;
    virtual QString getToken() const=0;
    virtual PSynHighlighterAttribute getTokenAttribute() const=0;
    virtual SynHighlighterTokenType getTokenType();
    virtual SynTokenKind getTokenKind() = 0;
    virtual int getTokenPos() = 0;
    virtual bool isKeyword(const QString& word);
    virtual void next() = 0;
    virtual void nextToEol();
    virtual void setState(SynRangeState rangeState, int braceLevel, int bracketLevel, int parenthesisLevel) = 0;
    virtual void setLine(const QString& newLine, int lineNumber) = 0;
    virtual void resetState() = 0;

    virtual QString languageName() = 0;
    virtual SynHighlighterLanguage language() = 0;

    virtual bool isSpaceChar(const QChar& ch);
    virtual bool isWordBreakChar(const QChar& ch);
    bool enabled() const;
    void setEnabled(bool value);

protected:
    PSynHighlighterAttribute mCommentAttribute;
    PSynHighlighterAttribute mIdentifierAttribute;
    PSynHighlighterAttribute mKeywordAttribute;
    PSynHighlighterAttribute mStringAttribute;
    PSynHighlighterAttribute mWhitespaceAttribute;
    PSynHighlighterAttribute mSymbolAttribute;

    void addAttribute(PSynHighlighterAttribute attribute);
    void clearAttributes();
    virtual int attributesCount() const;

    virtual PSynHighlighterAttribute getAttribute(const QString& name) const;

private:
    QMap<QString,PSynHighlighterAttribute> mAttributes;
    bool mEnabled;
    QSet<QChar> mWordBreakChars;
};

using PSynHighlighter = std::shared_ptr<SynHighlighter>;
using SynHighlighterList = QVector<PSynHighlighter>;

#endif // SYNHIGHLIGTERBASE_H
