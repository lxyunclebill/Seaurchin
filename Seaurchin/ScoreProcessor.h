#pragma once

#include "SusAnalyzer.h"
#include "Controller.h"
#include "ScriptResource.h"

struct PlayStatus {
    uint32_t JusticeCritical = 0;
    uint32_t Justice = 0;
    uint32_t Attack = 0;
    uint32_t Miss = 0;

    uint32_t AllNotes = 0;
    uint32_t Combo = 0;
    double CurrentGauge = 0.0;
    double GaugeDefaultMax = 60000.0;

public:
    void GetGaugeValue(int &fulfilled, double &rest);
    uint32_t GetScore();
};

enum class NoteAttribute {
    Invisible = 0,
    Finished,
    HellChecking,
    Completed,
    Activated,
};

class ScenePlayer;
class ScoreProcessor {
public:
    static std::vector<std::shared_ptr<SusDrawableNoteData>> DefaultDataValue;

    virtual void Reset() = 0;
    virtual void Update(std::vector<std::shared_ptr<SusDrawableNoteData>> &notes) = 0;
    virtual void MovePosition(double relative) = 0;
    virtual void Draw() = 0;
    virtual PlayStatus *GetPlayStatus() = 0;
};

class PlayableProcessor : public ScoreProcessor {
protected:
    ScenePlayer *Player;
    PlayStatus Status;
    std::shared_ptr<ControlState> CurrentState;
    std::vector<std::shared_ptr<SusDrawableNoteData>> &data = DefaultDataValue;
    bool isInHold = false, isInSlide = false, wasInHold = false, wasInSlide = false;
    SImage *imageHoldLight;
    double judgeWidthAttack;
    double judgeWidthJustice;
    double judgeWidthJusticeCritical;
    double judgeAdjustSlider;
    double judgeAdjustAirString;
    double judgeMultiplierAir;
    bool isAutoAir = false;

    void ProcessScore(std::shared_ptr<SusDrawableNoteData> notes);
    bool CheckJudgement(std::shared_ptr<SusDrawableNoteData> note);
    bool CheckHellJudgement(std::shared_ptr<SusDrawableNoteData> note);
    bool CheckAirJudgement(std::shared_ptr<SusDrawableNoteData> note);
    bool CheckAirActionJudgement(std::shared_ptr<SusDrawableNoteData> note);
    bool CheckHoldJudgement(std::shared_ptr<SusDrawableNoteData> note);
    bool CheckSlideJudgement(std::shared_ptr<SusDrawableNoteData> note);
    void IncrementCombo(std::shared_ptr<SusDrawableNoteData> note, double reltime);
    void IncrementComboEx(std::shared_ptr<SusDrawableNoteData> note);
    void IncrementComboHell(std::shared_ptr<SusDrawableNoteData> note, int state);
    void IncrementComboAir(std::shared_ptr<SusDrawableNoteData> note, double reltime);
    void ResetCombo(std::shared_ptr<SusDrawableNoteData> note);

public:
    PlayableProcessor(ScenePlayer *player);
    PlayableProcessor(ScenePlayer *player, bool autoAir);

    void SetAutoAir(bool flag);
    void SetJudgeWidths(double jc, double j, double a);
    void SetJudgeAdjusts(double jas, double jaa, double jma);
    void Reset() override;
    void Update(std::vector<std::shared_ptr<SusDrawableNoteData>> &notes) override;
    void MovePosition(double relative) override;
    void Draw() override;
    PlayStatus *GetPlayStatus() override;
};

class AutoPlayerProcessor : public ScoreProcessor {
protected:
    ScenePlayer *Player;
    PlayStatus Status;
    std::vector<std::shared_ptr<SusDrawableNoteData>> &data = DefaultDataValue;
    bool isInHold = false, isInSlide = false, isInAA = false, wasInHold = false, wasInSlide = false, wasInAA = false;

    void ProcessScore(std::shared_ptr<SusDrawableNoteData> notes);
    void IncrementCombo();

public:
    AutoPlayerProcessor(ScenePlayer *player);

    void Reset() override;
    void Update(std::vector<std::shared_ptr<SusDrawableNoteData>> &notes) override;
    void MovePosition(double relative) override;
    void Draw() override;
    PlayStatus *GetPlayStatus() override;
};