/*-
 * #%L
 * Codenjoy - it's a dojo-like platform from developers to developers.
 * %%
 * Copyright (C) 2018 Codenjoy
 * %%
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/gpl-3.0.html>.
 * #L%
 */
namespace Loderunner.Api
{
    public enum BoardElement : short
    {
        None = (short)' ',

        Brick = (short)'#',
        PitFill1 = (short)'1',
        PitFill2 = (short)'2',
        PitFill3 = (short)'3',
        PitFill4 = (short)'4',
        UndestroyableWall = (short)'☼',

        DrillPit = (short)'*',

        EnemyLadder = (short)'Q',
        EnemyLeft = (short)'«',
        EnemyRight = (short)'»',
        EnemyPipeLeft = (short)'<',
        EnemyPipeRight = (short)'>',
        EnemyPit = (short)'X',

        YellowGold = (short)'$',
        GreenGold = (short)'&',
        RedGold = (short)'@',

        HeroDie = (short)'Ѡ',
        HeroDrillLeft = (short)'Я',
        HeroDrillRight = (short)'R',
        HeroLadder = (short)'Y',
        HeroLeft = (short)'◄',
        HeroRight = (short)'►',
        HeroFallLeft = (short)']',
        HeroFallRight = (short)'[',
        HeroPipeLeft = (short)'{',
        HeroPipeRight = (short)'}',

        HeroShadowDie = (short)'x',
        HeroShadowDrillLeft = (short)'⊰',
        HeroShadowDrillRight = (short)'⊱',
        HeroShadowLadder = (short)'⍬',
        HeroShadowLeft = (short)'⊲',
        HeroShadowRight = (short)'⊳',
        HeroShadowFallLeft = (short)'⊅',
        HeroShadowFallRight = (short)'⊄',
        HeroShadowPipeLeft = (short)'⋜',
        HeroShadowPipeRight = (short)'⋝',

        OtherHeroDie = (short)'Z',
        OtherHeroDrillLeft = (short)'⌋',
        OtherHeroDrillRight = (short)'⌊',
        OtherHeroLeft = (short)')',
        OtherHeroRight = (short)'(',
        OtherHeroLadder = (short)'U',
        OtherHeroFallLeft = (short)'⊐',
        OtherHeroFallRight = (short)'⊏',
        OtherHeroPipeLeft = (short)'Э',
        OtherHeroPipeRight = (short)'Є',

        OtherHeroShadowDie = (short)'⋈',
        OtherHeroShadowDrillLeft = (short)'⋰',
        OtherHeroShadowDrillRight = (short)'⋱',
        OtherHeroShadowLeft = (short)'⋊',
        OtherHeroShadowRight = (short)'⋉',
        OtherHeroShadowLadder = (short)'⋕',
        OtherHeroShadowFallLeft = (short)'⋣',
        OtherHeroShadowFallRight = (short)'⋢',
        OtherHeroShadowPipeLeft = (short)'⊣',
        OtherHeroShadowPipeRight = (short)'⊢',

        Ladder = (short)'H',
        Pipe = (short)'~',

        Portal = (short)'⊛',

        TheShadowPill = (short)'S'
    }
}
