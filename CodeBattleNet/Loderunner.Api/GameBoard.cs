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
using System;
using System.Collections.Generic;
using System.Linq;

namespace Loderunner.Api
{
	public class GameBoard
	{
		public GameBoard(string boardString)
		{
			BoardString = boardString.Replace("\n", "");
		}

		public string BoardString { get; private set; }

		public int Size
		{
			get
			{
				return (int)Math.Sqrt(BoardString.Length);
			}
		}

		/// <summary>
		/// Returns the list of points for the given element type.
		/// </summary>
		/// <param name="element"></param>
		/// <returns></returns>
		public List<BoardPoint> FindAll(BoardElement element)
		{
			List<BoardPoint> result = new List<BoardPoint>();

			for (int i = 0; i < Size * Size; i++)
			{
				BoardPoint pt = GetPointByShift(i);

				if (HasElementAt(pt, element))
				{
					result.Add(pt);
				}
			}

			return result;
		}

		/// <summary>
		/// Returns a BoardElement object at coordinates x,y.
		/// </summary>
		/// <param name="point"></param>
		/// <returns></returns>
		public BoardElement GetAt(int x, int y)
		{
			return (BoardElement)BoardString[GetShiftByPoint(x, y)];
		}

		/// <summary>
		/// Returns True if BoardElement is at x,y coordinates.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="element"></param>
		/// <returns></returns>
		public bool HasElementAt(int x, int y, BoardElement element)
		{
			if (IsOutOfBoard(x, y))
			{
				return false;
			}

			return GetAt(x, y) == element;
		}

		/// <summary>
		/// Returns true if barrier is at x,y.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		public bool IsBarrierAt(int x, int y)
		{
			BoardPoint point = new BoardPoint(x, y);
			return GetBarriers().Contains(point);
		}

		/// <summary>
		/// Returns the point where your hero is.
		/// </summary>
		public BoardPoint GetMyPosition()
		{
			return FindAll(BoardElement.HeroDie)
				.Concat(FindAll(BoardElement.HeroDrillLeft))
				.Concat(FindAll(BoardElement.HeroDrillRight))
				.Concat(FindAll(BoardElement.HeroFallRight))
				.Concat(FindAll(BoardElement.HeroFallLeft))
				.Concat(FindAll(BoardElement.HeroLadder))
				.Concat(FindAll(BoardElement.HeroLeft))
				.Concat(FindAll(BoardElement.HeroRight))
				.Concat(FindAll(BoardElement.HeroPipeLeft))
				.Concat(FindAll(BoardElement.HeroPipeRight))
				.Concat(FindAll(BoardElement.HeroShadowDrillLeft))
				.Concat(FindAll(BoardElement.HeroShadowDrillRight))
				.Concat(FindAll(BoardElement.HeroShadowFallLeft))
				.Concat(FindAll(BoardElement.HeroShadowFallRight))
				.Concat(FindAll(BoardElement.HeroShadowLadder))
				.Concat(FindAll(BoardElement.HeroShadowLeft))
				.Concat(FindAll(BoardElement.HeroShadowRight))
				.Concat(FindAll(BoardElement.HeroShadowPipeLeft))
				.Concat(FindAll(BoardElement.HeroShadowPipeRight))
				.Single();
		}

		/// <summary>
		/// Returns False if your hero still alive.
		/// </summary>
		/// <returns></returns>
		public bool IsHeroDead()
		{
			return BoardString.Contains((char)BoardElement.HeroDie);
		}

		/// <summary>
		/// Return the list of points for other heroes.
		/// </summary>
		/// <returns></returns>
		public List<BoardPoint> GetEnemyPositions()
		{
			return FindAll(BoardElement.EnemyLadder)
				.Concat(FindAll(BoardElement.EnemyLeft))
				.Concat(FindAll(BoardElement.EnemyPipeLeft))
				.Concat(FindAll(BoardElement.EnemyPipeRight))
				.Concat(FindAll(BoardElement.EnemyRight))
				.Concat(FindAll(BoardElement.EnemyPit))
				.ToList();
		}

		/// <summary>
		/// Returns the list of points for other heroes.
		/// </summary>
		/// <returns></returns>
		public List<BoardPoint> GetOtherHeroPositions()
		{
			return FindAll(BoardElement.OtherHeroLadder)
				.Concat(FindAll(BoardElement.OtherHeroLeft))
				.Concat(FindAll(BoardElement.OtherHeroPipeLeft))
				.Concat(FindAll(BoardElement.OtherHeroPipeRight))
				.Concat(FindAll(BoardElement.OtherHeroRight))
				.Concat(FindAll(BoardElement.OtherHeroShadowLadder))
				.Concat(FindAll(BoardElement.OtherHeroShadowLeft))
				.Concat(FindAll(BoardElement.OtherHeroShadowRight))
				.Concat(FindAll(BoardElement.OtherHeroShadowPipeLeft))
				.Concat(FindAll(BoardElement.OtherHeroShadowPipeRight))
				.ToList();
		}

		/// <summary>
		/// Returns the list of points for elements with type BoardElement.TheShadowPill.
		/// </summary>
		/// <returns></returns>
		public List<BoardPoint> GetShadowPills()
		{
			return FindAll(BoardElement.TheShadowPill);
		}

		/// <summary>
		/// Returns the list of points for elements with type BoardElement.Portal.
		/// </summary>
		/// <returns></returns>
		public List<BoardPoint> GetPortals()
		{
			return FindAll(BoardElement.Portal);
		}

		/// <summary>
		/// Returns the list of walls element Points.
		/// </summary>
		/// <returns></returns>
		public List<BoardPoint> GetWallPositions()
		{
			return FindAll(BoardElement.Brick)
				.Concat(FindAll(BoardElement.UndestroyableWall))
				.ToList();
		}

		/// <summary>
		/// Returns the set of ladder Points.
		/// </summary>
		/// <returns></returns>
		public List<BoardPoint> GetLadderPositions()
		{
			HashSet<BoardPoint> set = new HashSet<BoardPoint>(
				FindAll(BoardElement.Ladder)
					.Concat(FindAll(BoardElement.HeroLadder))
					.Concat(FindAll(BoardElement.OtherHeroLadder))
					.Concat(FindAll(BoardElement.EnemyLadder))
					.Concat(FindAll(BoardElement.HeroShadowLadder))
					.Concat(FindAll(BoardElement.OtherHeroShadowLadder))
			);
			return set.ToList();
		}

		/// <summary>
		/// Return the list of points for elements with types:
		/// BoardElement.YellowGold, BoardElement.GreenGold, BoardElement.RedGold
		/// </summary>
		/// <returns></returns>
		public List<BoardPoint> GetGoldPositions()
		{
			return FindAll(BoardElement.YellowGold)
				.Concat(FindAll(BoardElement.GreenGold))
				.Concat(FindAll(BoardElement.RedGold))
				.ToList();
		}

		/// <summary>
		/// Returns the set of pipe BoardPoints.
		/// </summary>
		/// <returns></returns>
		public List<BoardPoint> GetPipePositions()
		{
			return FindAll(BoardElement.Pipe)
				.Concat(FindAll(BoardElement.HeroPipeLeft))
				.Concat(FindAll(BoardElement.HeroPipeRight))
				.Concat(FindAll(BoardElement.OtherHeroPipeLeft))
				.Concat(FindAll(BoardElement.OtherHeroPipeRight))
				.Concat(FindAll(BoardElement.EnemyPipeLeft))
				.Concat(FindAll(BoardElement.EnemyPipeRight))
				.Concat(FindAll(BoardElement.HeroShadowPipeLeft))
				.Concat(FindAll(BoardElement.HeroShadowPipeRight))
				.Concat(FindAll(BoardElement.OtherHeroShadowPipeLeft))
				.Concat(FindAll(BoardElement.OtherHeroShadowPipeRight))
				.ToList();
		}

		/// <summary>
		/// Returns the list of barriers Points.
		/// </summary>
		/// <returns></returns>
		public List<BoardPoint> GetBarriers()
		{
			return new HashSet<BoardPoint>(GetWallPositions())
				.ToList();
		}

		/// <summary>
		/// Check if near exists element of chosen type.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="element"></param>
		/// <returns></returns>
		public bool IsNearToElement(int x, int y, BoardElement element)
		{
			if (IsOutOfBoard(x, y))
				return false;

			BoardPoint p = new BoardPoint(x, y);
			return HasElementAt(p.ShiftBottom(), element)
				   || HasElementAt(p.ShiftTop(), element)
				   || HasElementAt(p.ShiftLeft(), element)
				   || HasElementAt(p.ShiftRight(), element);
		}

		/// <summary>
		/// Returns True if enemy exists in current point.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		public bool HasEnemyAt(int x, int y)
		{
			return GetEnemyPositions().Contains(new BoardPoint(x, y));
		}

		/// <summary>
		/// Returns True if other hero exists in current point.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		public bool HasOtherHeroAt(int x, int y)
		{
			return GetOtherHeroPositions().Contains(new BoardPoint(x, y));
		}

		/// <summary>
		/// Returns True if wall exists in current point.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		public bool HasWallAt(int x, int y)
		{
			return GetWallPositions().Contains(new BoardPoint(x, y));
		}

		/// <summary>
		/// Returns True if ladder exists in current point.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		public bool HasLadderAt(int x, int y)
		{
			return GetLadderPositions().Contains(new BoardPoint(x, y));
		}

		/// <summary>
		/// Returns True if golf exists in current point.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		public bool HasGoldAt(int x, int y)
		{
			return GetGoldPositions().Contains(new BoardPoint(x, y));
		}

		/// <summary>
		/// Returns True if pipe exists in current point.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		public bool HasPipeAt(int x, int y)
		{
			return GetPipePositions().Contains(new BoardPoint(x, y));
		}

		/// <summary>
		/// Returns True if shadow exists in current point.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		public bool HasShadowAt(int x, int y)
		{
			return HasElementAt(new BoardPoint(x, y),
				BoardElement.OtherHeroShadowLadder,
				BoardElement.OtherHeroShadowLeft,
				BoardElement.OtherHeroShadowRight,
				BoardElement.OtherHeroShadowPipeLeft,
				BoardElement.OtherHeroShadowPipeRight,
				BoardElement.HeroShadowDrillLeft,
				BoardElement.HeroShadowDrillRight,
				BoardElement.HeroShadowLadder,
				BoardElement.HeroShadowLeft,
				BoardElement.HeroShadowRight,
				BoardElement.HeroShadowFallLeft,
				BoardElement.HeroShadowFallRight,
				BoardElement.HeroShadowPipeLeft,
				BoardElement.HeroShadowPipeRight);
		}

		/// <summary>
		/// Counts the number of occurrences of element nearby.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="element"></param>
		/// <returns></returns>
		public int GetCountElementsNearToPoint(int x, int y, BoardElement element)
		{
			int count = 0;
			if (IsOutOfBoard(x, y))
				return count;

			BoardPoint point = new BoardPoint(x, y);

			if (HasElementAt(point.ShiftLeft(), element))
				count++;
			if (HasElementAt(point.ShiftRight(), element))
				count++;
			if (HasElementAt(point.ShiftTop(), element))
				count++;
			if (HasElementAt(point.ShiftBottom(), element))
				count++;
			return count;
		}

		public void PrintBoard()
		{
			for (int i = 0; i < Size; i++)
			{
				Console.WriteLine(BoardString.Substring(i * Size, Size));
			}
		}

		private bool HasElementAt(BoardPoint point, params BoardElement[] elements)
		{
			return elements.Any(elem => HasElementAt(point.X, point.Y, elem));
		}

		private int GetShiftByPoint(BoardPoint point)
		{
			return point.Y * Size + point.X;
		}

		private int GetShiftByPoint(int x, int y)
		{
			return y * Size + x;
		}

		private BoardPoint GetPointByShift(int shift)
		{
			return new BoardPoint(shift % Size, shift / Size);
		}

		private bool IsOutOfBoard(int x, int y)
		{
			return x >= Size || y >= Size || x < 0 || y < 0;
		}
	}
}
