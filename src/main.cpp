#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/TextInput.hpp>

#define MORE_ICONS_EVENTS
#include "more-icons/MoreIcons.hpp"

using namespace geode::prelude;

namespace IconSaveFix {

    constexpr int PAGE_SIZE = 3;

    struct IconKit {
        std::string name;

        int cube = 1;
        int ship = 1;
        int ball = 1;
        int ufo = 1;
        int wave = 1;
        int robot = 1;
        int spider = 1;
        int swing = 1;
        int jetpack = 1;

        int color1 = 0;
        int color2 = 3;
        int glowColor = 0;
        bool glow = false;

        std::string customCube;
        std::string customShip;
        std::string customBall;
        std::string customUfo;
        std::string customWave;
        std::string customRobot;
        std::string customSpider;
        std::string customSwing;
        std::string customJetpack;
    };

    // ========================================================
    // SAVE SYSTEM
    //
    // Em vez de salvar um matjson inteiro, cada valor recebe
    // sua própria chave persistente no save do mod.
    // ========================================================

    std::string key(
        int index,
        std::string const& property
    ) {
        return fmt::format(
            "kit-{}-{}",
            index,
            property
        );
    }

    template <class T>
    T read(
        int index,
        std::string const& property,
        T fallback
    ) {
        return Mod::get()->getSavedValue<T>(
            key(index, property),
            fallback
        );
    }

    template <class T>
    void write(
        int index,
        std::string const& property,
        T const& value
    ) {
        Mod::get()->setSavedValue(
            key(index, property),
            value
        );
    }

    void writeKit(
        int index,
        IconKit const& kit
    ) {
        write(index, "name", kit.name);

        write(index, "cube", kit.cube);
        write(index, "ship", kit.ship);
        write(index, "ball", kit.ball);
        write(index, "ufo", kit.ufo);
        write(index, "wave", kit.wave);
        write(index, "robot", kit.robot);
        write(index, "spider", kit.spider);
        write(index, "swing", kit.swing);
        write(index, "jetpack", kit.jetpack);

        write(index, "color1", kit.color1);
        write(index, "color2", kit.color2);
        write(index, "glow-color", kit.glowColor);
        write(index, "glow", kit.glow);

        write(
            index,
            "custom-cube",
            kit.customCube
        );

        write(
            index,
            "custom-ship",
            kit.customShip
        );

        write(
            index,
            "custom-ball",
            kit.customBall
        );

        write(
            index,
            "custom-ufo",
            kit.customUfo
        );

        write(
            index,
            "custom-wave",
            kit.customWave
        );

        write(
            index,
            "custom-robot",
            kit.customRobot
        );

        write(
            index,
            "custom-spider",
            kit.customSpider
        );

        write(
            index,
            "custom-swing",
            kit.customSwing
        );

        write(
            index,
            "custom-jetpack",
            kit.customJetpack
        );
    }

    IconKit readKit(int index) {
        IconKit kit;

        kit.name =
            read<std::string>(
                index,
                "name",
                fmt::format(
                    "Kit {}",
                    index + 1
                )
            );

        kit.cube =
            read<int>(
                index,
                "cube",
                1
            );

        kit.ship =
            read<int>(
                index,
                "ship",
                1
            );

        kit.ball =
            read<int>(
                index,
                "ball",
                1
            );

        kit.ufo =
            read<int>(
                index,
                "ufo",
                1
            );

        kit.wave =
            read<int>(
                index,
                "wave",
                1
            );

        kit.robot =
            read<int>(
                index,
                "robot",
                1
            );

        kit.spider =
            read<int>(
                index,
                "spider",
                1
            );

        kit.swing =
            read<int>(
                index,
                "swing",
                1
            );

        kit.jetpack =
            read<int>(
                index,
                "jetpack",
                1
            );

        kit.color1 =
            read<int>(
                index,
                "color1",
                0
            );

        kit.color2 =
            read<int>(
                index,
                "color2",
                3
            );

        kit.glowColor =
        read<int>(
        index,
        "glow-color",
        kit.color2
    );

        kit.glow =
            read<bool>(
                index,
                "glow",
                false
            );

        kit.customCube =
            read<std::string>(
                index,
                "custom-cube",
                ""
            );

        kit.customShip =
            read<std::string>(
                index,
                "custom-ship",
                ""
            );

        kit.customBall =
            read<std::string>(
                index,
                "custom-ball",
                ""
            );

        kit.customUfo =
            read<std::string>(
                index,
                "custom-ufo",
                ""
            );

        kit.customWave =
            read<std::string>(
                index,
                "custom-wave",
                ""
            );

        kit.customRobot =
            read<std::string>(
                index,
                "custom-robot",
                ""
            );

        kit.customSpider =
            read<std::string>(
                index,
                "custom-spider",
                ""
            );

        kit.customSwing =
            read<std::string>(
                index,
                "custom-swing",
                ""
            );

        kit.customJetpack =
            read<std::string>(
                index,
                "custom-jetpack",
                ""
            );

        return kit;
    }

    std::vector<IconKit> loadKits() {
        std::vector<IconKit> kits;

        int count =
            Mod::get()->getSavedValue<int>(
                "kit-count",
                0
            );

        if (count < 0) {
            count = 0;
        }

        // Proteção caso o save fique corrompido.
        if (count > 500) {
            count = 500;
        }

        kits.reserve(count);

        for (int i = 0; i < count; i++) {
            kits.push_back(
                readKit(i)
            );
        }

        return kits;
    }

    void saveKits(
        std::vector<IconKit> const& kits
    ) {
        // Regravamos todos os índices.
        //
        // Isso é especialmente importante depois de apagar
        // um kit do meio da lista.
        for (
            int i = 0;
            i < static_cast<int>(kits.size());
            i++
        ) {
            writeKit(
                i,
                kits[i]
            );
        }

        Mod::get()->setSavedValue(
            "kit-count",
            static_cast<int>(
                kits.size()
            )
        );
    }

    // ========================================================
    // MORE ICONS
    // ========================================================

    std::string customIconName(
        IconType type
    ) {
        auto info =
            more_icons::activeIcon(type);

        if (!info) {
            return "";
        }

        // More Icons can report traditional texture-pack icons as
        // vanilla=true AND texturePack=true. Those still need to be
        // persisted by name so we can restore the exact pack icon.
        if (info->isVanilla() && !info->inTexturePack()) {
            return "";
        }

        return info->getName();
    }

    void applyCustomIcon(
        IconType type,
        std::string const& name
    ) {
        if (name.empty()) {
            more_icons::setIcon(
                nullptr,
                type
            );

            return;
        }

        auto info =
            more_icons::getIcon(
                name,
                type
            );

        if (!info) {
            log::warn(
                "Icon Save Fix: More Icons icon '{}' not found",
                name
            );

            more_icons::setIcon(
                nullptr,
                type
            );

            return;
        }

        more_icons::setIcon(
            info,
            type
        );
    }

    // ========================================================
    // CAPTURE CURRENT KIT
    // ========================================================

    IconKit captureCurrentKit(
        std::string name
    ) {
        auto gm =
            GameManager::sharedState();

        IconKit kit;

        kit.name =
            std::move(name);

        kit.cube =
            gm->getPlayerFrame();

        kit.ship =
            gm->getPlayerShip();

        kit.ball =
            gm->getPlayerBall();

        kit.ufo =
            gm->getPlayerBird();

        kit.wave =
            gm->getPlayerDart();

        kit.robot =
            gm->getPlayerRobot();

        kit.spider =
            gm->getPlayerSpider();

        kit.swing =
            gm->getPlayerSwing();

        kit.jetpack =
            gm->getPlayerJetpack();

        kit.color1 =
            gm->getPlayerColor();

        kit.color2 =
            gm->getPlayerColor2();

        kit.glowColor =
            gm->getPlayerGlowColor();

        kit.glow =
            gm->getPlayerGlow();

        kit.customCube =
            customIconName(
                IconType::Cube
            );

        kit.customShip =
            customIconName(
                IconType::Ship
            );

        kit.customBall =
            customIconName(
                IconType::Ball
            );

        kit.customUfo =
            customIconName(
                IconType::Ufo
            );

        kit.customWave =
            customIconName(
                IconType::Wave
            );

        kit.customRobot =
            customIconName(
                IconType::Robot
            );

        kit.customSpider =
            customIconName(
                IconType::Spider
            );

        kit.customSwing =
            customIconName(
                IconType::Swing
            );

        kit.customJetpack =
            customIconName(
                IconType::Jetpack
            );

        return kit;
    }

    // ========================================================
    // APPLY KIT
    // ========================================================

    void applyKit(
        IconKit const& kit
    ) {
        auto gm =
            GameManager::sharedState();

        // Primeiro restaura os IDs vanilla.
        gm->setPlayerFrame(
            kit.cube
        );

        gm->setPlayerShip(
            kit.ship
        );

        gm->setPlayerBall(
            kit.ball
        );

        gm->setPlayerBird(
            kit.ufo
        );

        gm->setPlayerDart(
            kit.wave
        );

        gm->setPlayerRobot(
            kit.robot
        );

        gm->setPlayerSpider(
            kit.spider
        );

        gm->setPlayerSwing(
            kit.swing
        );

        gm->setPlayerJetpack(
            kit.jetpack
        );

        gm->setPlayerColor(
            kit.color1
        );

        gm->setPlayerColor2(
            kit.color2
        );

        gm->m_playerGlowColor =
            kit.glowColor;

        gm->setPlayerGlow(
            kit.glow
        );

        // Depois coloca os overrides do More Icons.
        applyCustomIcon(
            IconType::Cube,
            kit.customCube
        );

        applyCustomIcon(
            IconType::Ship,
            kit.customShip
        );

        applyCustomIcon(
            IconType::Ball,
            kit.customBall
        );

        applyCustomIcon(
            IconType::Ufo,
            kit.customUfo
        );

        applyCustomIcon(
            IconType::Wave,
            kit.customWave
        );

        applyCustomIcon(
            IconType::Robot,
            kit.customRobot
        );

        applyCustomIcon(
            IconType::Spider,
            kit.customSpider
        );

        applyCustomIcon(
            IconType::Swing,
            kit.customSwing
        );

        applyCustomIcon(
            IconType::Jetpack,
            kit.customJetpack
        );
    }

    // ========================================================
    // PREVIEW HELPERS
    // ========================================================

    int iconIDForType(
        IconKit const& kit,
        IconType type
    ) {
        switch (type) {
            case IconType::Cube:
                return kit.cube;

            case IconType::Ship:
                return kit.ship;

            case IconType::Ball:
                return kit.ball;

            case IconType::Ufo:
                return kit.ufo;

            case IconType::Wave:
                return kit.wave;

            case IconType::Robot:
                return kit.robot;

            case IconType::Spider:
                return kit.spider;

            case IconType::Swing:
                return kit.swing;

            case IconType::Jetpack:
                return kit.jetpack;

            default:
                return 1;
        }
    }

    std::string customNameForType(
        IconKit const& kit,
        IconType type
    ) {
        switch (type) {
            case IconType::Cube:
                return kit.customCube;

            case IconType::Ship:
                return kit.customShip;

            case IconType::Ball:
                return kit.customBall;

            case IconType::Ufo:
                return kit.customUfo;

            case IconType::Wave:
                return kit.customWave;

            case IconType::Robot:
                return kit.customRobot;

            case IconType::Spider:
                return kit.customSpider;

            case IconType::Swing:
                return kit.customSwing;

            case IconType::Jetpack:
                return kit.customJetpack;

            default:
                return "";
        }
    }

    char const* shortTypeName(
        IconType type
    ) {
        switch (type) {
            case IconType::Cube:
                return "C";

            case IconType::Ship:
                return "S";

            case IconType::Ball:
                return "B";

            case IconType::Ufo:
                return "U";

            case IconType::Wave:
                return "W";

            case IconType::Robot:
                return "R";

            case IconType::Spider:
                return "SP";

            case IconType::Swing:
                return "SW";

            case IconType::Jetpack:
                return "J";

            default:
                return "?";
        }
    }

    // Creates the preview for a saved slot.
    //
    // We first build the normal GD SimplePlayer using the saved vanilla ID.
    // If this slot has a More Icons / texture-pack identity, we temporarily
    // make that icon active, ask More Icons to render this SimplePlayer, then
    // immediately restore the user's real active icon. This keeps opening the
    // popup from changing the actual selected kit.
    SimplePlayer* createVanillaPreview(
        IconKit const& kit,
        IconType type
    ) {
        auto preview =
            SimplePlayer::create(
                iconIDForType(
                    kit,
                    type
                )
            );

        if (!preview) {
            return nullptr;
        }

        preview->updatePlayerFrame(
            iconIDForType(
                kit,
                type
            ),
            type
        );

        auto custom =
            customNameForType(
                kit,
                type
            );

        if (!custom.empty()) {
            auto wanted =
                more_icons::getIcon(
                    custom,
                    type
                );

            if (wanted) {
                // Save the current More Icons selection for this type.
                auto previous =
                    more_icons::activeIcon(type);

                // Render the saved custom / texture-pack icon.
                more_icons::setIcon(
                    wanted,
                    type
                );

                more_icons::updateSimplePlayer(
                    preview,
                    type
                );

                // Restore the real selection immediately.
                more_icons::setIcon(
                    previous,
                    type
                );
            }
            else {
                log::warn(
                    "Icon Save Fix: preview icon '{}' not found",
                    custom
                );
            }
        }

        auto gm =
            GameManager::sharedState();

        preview->setColor(
            gm->colorForIdx(
                kit.color1
            )
        );

        preview->setSecondColor(
            gm->colorForIdx(
                kit.color2
            )
        );

        if (kit.glow) {
    preview->setGlowOutline(
        gm->colorForIdx(
            kit.glowColor
        )
    );
}

        return preview;
    }

}

// ============================================================
// POPUP
// ============================================================

class IconSavePopup : public Popup {
protected:
    std::vector<
        IconSaveFix::IconKit
    > m_kits;

    TextInput* m_nameInput =
        nullptr;

    CCMenu* m_listMenu =
        nullptr;

    CCLabelBMFont* m_pageLabel =
        nullptr;

    int m_page = 0;

    bool init() {
        if (!Popup::init(
            420.f,
            300.f
        )) {
            return false;
        }

        this->setTitle(
            "Icon Save Fix"
        );

        m_kits =
            IconSaveFix::loadKits();

        auto size =
            m_mainLayer
                ->getContentSize();

        // ====================================================
        // INPUT
        // ====================================================

        m_nameInput =
            TextInput::create(
                205.f,
                "Kit name"
            );

        m_nameInput->setPosition({
            size.width / 2.f - 30.f,
            size.height - 50.f
        });

        m_mainLayer->addChild(
            m_nameInput
        );

        // ====================================================
        // SAVE BUTTON
        // ====================================================

        auto saveSprite =
            ButtonSprite::create(
                "Save",
                65,
                true,
                "goldFont.fnt",
                "GJ_button_01.png",
                30.f,
                0.8f
            );

        auto saveButton =
            CCMenuItemSpriteExtra::create(
                saveSprite,
                this,
                menu_selector(
                    IconSavePopup::onSave
                )
            );

        auto saveMenu =
            CCMenu::create();

        saveMenu->setPosition({
            size.width - 55.f,
            size.height - 50.f
        });

        saveMenu->addChild(
            saveButton
        );

        m_mainLayer->addChild(
            saveMenu
        );

        // ====================================================
        // LIST
        // ====================================================

        m_listMenu =
            CCMenu::create();

        m_listMenu->setPosition({
            0.f,
            0.f
        });

        m_mainLayer->addChild(
            m_listMenu
        );

        // ====================================================
        // PAGE CONTROLS
        // ====================================================

        auto prevSprite =
            CCSprite::createWithSpriteFrameName(
                "GJ_arrow_01_001.png"
            );

        auto nextSprite =
            CCSprite::createWithSpriteFrameName(
                "GJ_arrow_01_001.png"
            );

        if (prevSprite) {
            prevSprite->setScale(
                0.5f
            );
        }

        if (nextSprite) {
            nextSprite->setScale(
                0.5f
            );

            nextSprite->setFlipX(
                true
            );
        }

        auto pageMenu =
            CCMenu::create();

        pageMenu->setPosition({
            size.width / 2.f,
            22.f
        });

        if (prevSprite) {
            auto prev =
                CCMenuItemSpriteExtra::create(
                    prevSprite,
                    this,
                    menu_selector(
                        IconSavePopup::onPrev
                    )
                );

            prev->setPosition({
                -90.f,
                0.f
            });

            pageMenu->addChild(
                prev
            );
        }

        if (nextSprite) {
            auto next =
                CCMenuItemSpriteExtra::create(
                    nextSprite,
                    this,
                    menu_selector(
                        IconSavePopup::onNext
                    )
                );

            next->setPosition({
                90.f,
                0.f
            });

            pageMenu->addChild(
                next
            );
        }

        m_mainLayer->addChild(
            pageMenu
        );

        m_pageLabel =
            CCLabelBMFont::create(
                "",
                "goldFont.fnt"
            );

        m_pageLabel->setScale(
            0.42f
        );

        m_pageLabel->setPosition({
            size.width / 2.f,
            22.f
        });

        m_mainLayer->addChild(
            m_pageLabel
        );

        refreshList();

        return true;
    }

    // ========================================================
    // CARD
    // ========================================================

    void createKitCard(
        int index,
        float centerY
    ) {
        auto size =
            m_mainLayer
                ->getContentSize();

        auto const& kit =
            m_kits[index];

        // ----------------------------------------------------
        // Card background
        // ----------------------------------------------------

        auto bg =
            CCScale9Sprite::create(
                "square02b_001.png"
            );

        if (bg) {
            bg->setContentSize({
                345.f,
                60.f
            });

            bg->setOpacity(
                85
            );

            bg->setPosition({
                size.width / 2.f,
                centerY
            });

            m_listMenu->addChild(
                bg
            );
        }

        // ----------------------------------------------------
        // Invisible/transparent-ish apply button covering card
        // ----------------------------------------------------

        auto applySprite =
            ButtonSprite::create(
                "",
                330,
                true,
                "bigFont.fnt",
                "GJ_button_04.png",
                52.f,
                0.1f
            );

        applySprite->setOpacity(
            25
        );

        auto applyButton =
            CCMenuItemSpriteExtra::create(
                applySprite,
                this,
                menu_selector(
                    IconSavePopup::onApply
                )
            );

        applyButton->setTag(
            index
        );

        applyButton->setPosition({
            size.width / 2.f - 5.f,
            centerY
        });

        m_listMenu->addChild(
            applyButton
        );

        // ----------------------------------------------------
        // Kit name
        // ----------------------------------------------------

        auto name =
            CCLabelBMFont::create(
                kit.name.c_str(),
                "goldFont.fnt"
            );

        name->setScale(
            0.42f
        );

        name->setPosition({
            size.width / 2.f - 10.f,
            centerY + 19.f
        });

        m_listMenu->addChild(
            name
        );

        // ----------------------------------------------------
        // 9 icon previews
        // ----------------------------------------------------

        IconType types[] = {
            IconType::Cube,
            IconType::Ship,
            IconType::Ball,
            IconType::Ufo,
            IconType::Wave,
            IconType::Robot,
            IconType::Spider,
            IconType::Swing,
            IconType::Jetpack
        };

        float startX =
            size.width / 2.f - 126.f;

        float spacing =
            31.5f;

        for (int j = 0; j < 9; j++) {
            auto type =
                types[j];

            float x =
                startX +
                spacing * j;

            auto preview =
                IconSaveFix::
                    createVanillaPreview(
                        kit,
                        type
                    );

            if (preview) {
                preview->setPosition({
                    x,
                    centerY - 7.f
                });

                // Some modes are naturally larger than others.
                float scale = 0.38f;

                if (
                    type == IconType::Ship ||
                    type == IconType::Ufo ||
                    type == IconType::Robot ||
                    type == IconType::Spider ||
                    type == IconType::Swing ||
                    type == IconType::Jetpack
                ) {
                    scale = 0.31f;
                }

                preview->setScale(
                    scale
                );

                m_listMenu->addChild(
                    preview
                );
            }
            else {
                auto fallback =
                    CCLabelBMFont::create(
                        IconSaveFix::
                            shortTypeName(type),
                        "bigFont.fnt"
                    );

                fallback->setScale(
                    0.25f
                );

                fallback->setPosition({
                    x,
                    centerY - 7.f
                });

                m_listMenu->addChild(
                    fallback
                );
            }

            // Custom marker.
            //
            // Even before we hook the More Icons renderer into
            // SimplePlayer, this tells us that this slot contains
            // a saved custom icon rather than only the vanilla ID.
            auto custom =
                IconSaveFix::
                    customNameForType(
                        kit,
                        type
                    );

            if (!custom.empty()) {
                auto marker =
                    CCLabelBMFont::create(
                        "+",
                        "goldFont.fnt"
                    );

                marker->setScale(
                    0.28f
                );

                marker->setPosition({
                    x + 8.f,
                    centerY + 2.f
                });

                m_listMenu->addChild(
                    marker
                );
            }
        }

        // ----------------------------------------------------
        // Delete
        // ----------------------------------------------------

        auto deleteSprite =
            CCSprite::createWithSpriteFrameName(
                "GJ_deleteIcon_001.png"
            );

        if (deleteSprite) {
            deleteSprite->setScale(
                0.62f
            );

            auto deleteButton =
                CCMenuItemSpriteExtra::create(
                    deleteSprite,
                    this,
                    menu_selector(
                        IconSavePopup::onDelete
                    )
                );

            deleteButton->setTag(
                index
            );

            deleteButton->setPosition({
                size.width - 30.f,
                centerY
            });

            m_listMenu->addChild(
                deleteButton
            );
        }
    }

    // ========================================================
    // REFRESH
    // ========================================================

    void refreshList() {
        if (!m_listMenu) {
            return;
        }

        m_listMenu
            ->removeAllChildren();

        int pageCount =
            std::max(
                1,
                static_cast<int>(
                    (
                        m_kits.size() +
                        IconSaveFix::PAGE_SIZE -
                        1
                    ) /
                    IconSaveFix::PAGE_SIZE
                )
            );

        if (m_page >= pageCount) {
            m_page =
                pageCount - 1;
        }

        if (m_page < 0) {
            m_page = 0;
        }

        if (m_pageLabel) {
            m_pageLabel->setString(
                fmt::format(
                    "{}/{}",
                    m_page + 1,
                    pageCount
                ).c_str()
            );
        }

        auto size =
            m_mainLayer
                ->getContentSize();

        if (m_kits.empty()) {
            auto empty =
                CCLabelBMFont::create(
                    "No saved kits yet",
                    "bigFont.fnt"
                );

            empty->setScale(
                0.45f
            );

            empty->setPosition({
                size.width / 2.f,
                size.height / 2.f
            });

            m_listMenu->addChild(
                empty
            );

            return;
        }

        int start =
            m_page *
            IconSaveFix::PAGE_SIZE;

        int end =
            std::min(
                start +
                    IconSaveFix::PAGE_SIZE,

                static_cast<int>(
                    m_kits.size()
                )
            );

        float firstY =
            size.height - 102.f;

        float spacing =
            67.f;

        for (
            int i = start;
            i < end;
            i++
        ) {
            float y =
                firstY -
                static_cast<float>(
                    i - start
                ) *
                spacing;

            createKitCard(
                i,
                y
            );
        }
    }

    // ========================================================
    // SAVE
    // ========================================================

    void onSave(CCObject*) {
        std::string name;

        if (m_nameInput) {
            name =
                m_nameInput
                    ->getString();
        }

        if (name.empty()) {
            name =
                fmt::format(
                    "Kit {}",
                    m_kits.size() + 1
                );
        }

        auto kit =
            IconSaveFix::
                captureCurrentKit(
                    name
                );

        m_kits.push_back(
            kit
        );

        IconSaveFix::saveKits(
            m_kits
        );

        // Reload from persistent storage immediately.
        //
        // Besides keeping the UI and disk state identical, this
        // also catches save mistakes immediately rather than only
        // after reopening the Garage.
        m_kits =
            IconSaveFix::loadKits();

        if (m_nameInput) {
            m_nameInput
                ->setString("");
        }

        if (!m_kits.empty()) {
            m_page =
                static_cast<int>(
                    (
                        m_kits.size() -
                        1
                    ) /
                    IconSaveFix::PAGE_SIZE
                );
        }

        refreshList();

        Notification::create(
            "Icon kit saved!",
            NotificationIcon::Success
        )->show();
    }

    // ========================================================
    // APPLY
    // ========================================================

    void onApply(
        CCObject* sender
    ) {
        auto node =
            static_cast<CCNode*>(
                sender
            );

        int index =
            node->getTag();

        if (
            index < 0 ||
            index >=
                static_cast<int>(
                    m_kits.size()
                )
        ) {
            return;
        }

        auto appliedKit =
            m_kits[index];

        IconSaveFix::applyKit(
            appliedKit
        );

        auto kitName =
            appliedKit.name;

        Notification::create(
            fmt::format(
                "Applied {}",
                kitName
            ),
            NotificationIcon::Success
        )->show();

        this->onClose(
            nullptr
        );

        auto scene =
            CCDirector::
                sharedDirector()
                ->getRunningScene();

        if (!scene) {
            return;
        }

        auto children =
            scene->getChildren();

        if (!children) {
            return;
        }

        for (
            unsigned int i = 0;
            i < children->count();
            i++
        ) {
            auto child =
                children->objectAtIndex(i);

            if (
                auto garage =
                    typeinfo_cast<
                        GJGarageLayer*
                    >(child)
            ) {
                // setupIconSelect() is initialization code. Calling it again
                // stacks another set of cursors / page dots over the old UI.
                // selectTab() is the normal refresh path used by the Garage.
                auto currentType =
                    garage->m_iconType;

                garage->selectTab(
                    currentType
                );

                if (garage->m_playerObject) {
                    // Always restore the vanilla frame first. This fixes
                    // custom/texture-pack -> vanilla kit switches.
                    int currentID =
                        IconSaveFix::iconIDForType(
                            appliedKit,
                            currentType
                        );

                    garage->m_playerObject
                        ->updatePlayerFrame(
                            currentID,
                            currentType
                        );

                    // Then let More Icons replace it when this kit has an
                    // active custom / texture-pack icon for this type.
                    more_icons::updateSimplePlayer(
                        garage->m_playerObject,
                        currentType
                    );
                }

                garage->updatePlayerColors();

                break;
            }
        }
    }

    // ========================================================
    // DELETE
    // ========================================================

    void onDelete(
        CCObject* sender
    ) {
        auto node =
            static_cast<CCNode*>(
                sender
            );

        int index =
            node->getTag();

        if (
            index < 0 ||
            index >=
                static_cast<int>(
                    m_kits.size()
                )
        ) {
            return;
        }

        m_kits.erase(
            m_kits.begin() +
            index
        );

        IconSaveFix::saveKits(
            m_kits
        );

        // Same idea as Save: immediately prove the persistent
        // state can be read back.
        m_kits =
            IconSaveFix::loadKits();

        refreshList();

        Notification::create(
            "Kit deleted",
            NotificationIcon::Success
        )->show();
    }

    void onPrev(CCObject*) {
        if (m_page > 0) {
            --m_page;
            refreshList();
        }
    }

    void onNext(CCObject*) {
        int pageCount =
            std::max(
                1,
                static_cast<int>(
                    (
                        m_kits.size() +
                        IconSaveFix::PAGE_SIZE -
                        1
                    ) /
                    IconSaveFix::PAGE_SIZE
                )
            );

        if (
            m_page + 1 <
            pageCount
        ) {
            ++m_page;
            refreshList();
        }
    }

public:
    static IconSavePopup* create() {
        auto ret =
            new IconSavePopup();

        if (ret->init()) {
            ret->autorelease();
            return ret;
        }

        delete ret;

        return nullptr;
    }
};

// ============================================================
// GARAGE
// ============================================================

class $modify(
    IconSaveGarageLayer,
    GJGarageLayer
) {
    bool init() {
        if (
            !GJGarageLayer::init()
        ) {
            return false;
        }

        auto menu =
            this->getChildByID(
                "shards-menu"
            );

        if (!menu) {
            menu =
                this->getChildByID(
                    "category-menu"
                );
        }

        if (!menu) {
            auto fallback =
                CCMenu::create();

            fallback->setID(
                "icon-save-fix-menu"_spr
            );

            fallback->setPosition({
                35.f,
                35.f
            });

            this->addChild(
                fallback,
                100
            );

            menu = fallback;
        }

        auto sprite =
            CCSprite::createWithSpriteFrameName(
                "GJ_plusBtn_001.png"
            );

        if (!sprite) {
            sprite =
                CCSprite::createWithSpriteFrameName(
                    "GJ_optionsBtn_001.png"
                );
        }

        if (!sprite) {
            return true;
        }

        sprite->setScale(
            0.7f
        );

        auto button =
            CCMenuItemSpriteExtra::create(
                sprite,
                this,
                menu_selector(
                    IconSaveGarageLayer::
                        onIconSaveFix
                )
            );

        button->setID(
            "icon-save-fix-button"_spr
        );

        menu->addChild(
            button
        );

        if (menu->getLayout()) {
            menu->updateLayout();
        }
        else {
            button->setPosition({
                0.f,
                0.f
            });
        }

        return true;
    }

    void onIconSaveFix(
        CCObject*
    ) {
        auto popup =
            IconSavePopup::create();

        if (popup) {
            popup->show();
        }
    }
};