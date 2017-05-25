package com.parser;
import java.io.File;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.poi.*;
import org.apache.poi.openxml4j.exceptions.InvalidFormatException;
import org.apache.poi.ss.format.CellFormatType;
import org.apache.poi.ss.formula.FormulaType;
import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.CellType;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.WorkbookFactory;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

public class Main {

	private static XSSFWorkbook wb;
	
	private enum TypeObject { Papers, Session, Track};
	
	private static String GetCelluleValeur(String sheet ,int ligne ,int colonne, XSSFWorkbook wbf)
	{
		String res = "";
		//System.out.println("Sheet : " + sheet);
		XSSFSheet feuille =  wbf.getSheet(sheet);
		Row row = feuille.getRow(ligne);
		if (row == null) {
			row = feuille.createRow(ligne);
		}
		Cell cell = null;
		cell = row.getCell((short) colonne);
		res = cell.getStringCellValue();
		
		return res;
	}
	
	private static String parseIntAndFloat(String raw)
	{
		String res = "";
		Pattern p = Pattern.compile("(\\+|-)?([0-9]+(.?[0-9])+)");
		Matcher m = p.matcher(raw);
		if(m.find())
			res = m.group();
		if(res.contains(":"))
		{
			String[] splited = res.split(":");
			int hours = Integer.parseInt(splited[0]);
			int minutes = Integer.parseInt(splited[1]);
			res = "" + (hours + minutes/60.0);
		}
		return res;
	}
	
	private static String checkIntervalle(String raw)
	{
		String res = raw;
		if(raw.contains(":"))
		{
			if(raw.contains("["))
			{
				String[] splited = raw.split(",");
				String[] left = splited[0].split(":");
				String[] right = splited[1].split(":");
				
				String tempminl = left[1].substring(0, left[1].length());
				String tempheurel = left[0].substring(1, left[0].length());
				String tempminr = right[1].substring(0, right[1].length()-1);
				String tempheurer = right[0].substring(0, right[0].length());
				int hourl = Integer.parseInt(tempheurel);
				int minutel = Integer.parseInt(tempminl);
				int hourr = Integer.parseInt(tempheurer);
				int minuter = Integer.parseInt(tempminr);
				res = "[" + (hourl + minutel/60.0)+","+ (hourr + minuter/60.0)  + "]";
			}
		}
		return res;
	}
	
	public static ArrayList<String> Lignes(String sheet, TypeObject to)
	{
		ArrayList<String> res = new ArrayList<String>();
		System.out.println("Onglet : "+sheet);
		XSSFSheet feuille =  wb.getSheet(sheet);
		Row row = null;
		String temp;
		int i = 0;
		for (Iterator rowIt = feuille.rowIterator(); rowIt.hasNext();) 
		{
			if(i!=0)
			{
				row = (Row) rowIt.next();
				temp = (Colonnes(sheet, i, to));
				if(temp.length()>0)
				{
					//System.out.println(temp);
					//System.out.println(temp.charAt(0));
					if (temp.charAt(0)!='-')
						res.add(temp);
				}
				else
					break;
			}
			i++;
		}
		return res;
	}
	
	public static String Colonnes(String sheet, int ligne, TypeObject to)
	{
		String res = "";
		XSSFSheet feuille =  wb.getSheet(sheet);
		Row row = feuille.getRow(ligne);
		Cell cell = null;
		boolean continuer = true;
		try
		{
			if(row!=null)
			{
				for (Iterator cellIt = row.cellIterator(); cellIt.hasNext();) 
				{
					cell = (Cell) cellIt.next();
					int idcolonne = cell.getColumnIndex();
					switch (to) {
					/*
					 * 0  ID
					 * 2  Track ID
					 * 4  Session ID
					 * 26 Duration
					 * 32 Fuseau
					 * 32 Dispo 1
					 * 34 Dispo 2
					 * 35 Dispo 3
					 */
						case Papers : 
							if(idcolonne != 0 && idcolonne != 2 && idcolonne != 4
								&& idcolonne != 26 && idcolonne != 32 && idcolonne != 33
								&& idcolonne != 34 && idcolonne != 35)
								continuer = false;
							break;
						default :
							break;
					}
					if(continuer)
					{
						if(cell.getCellTypeEnum() == CellType.STRING)
							if(idcolonne != 32)
								res = res + checkIntervalle(cell.getStringCellValue())+"|";
							else
								res = res + parseIntAndFloat(cell.getStringCellValue()) + "|";
						else if(idcolonne == 26 && res.length()>0)
						{
							res = res + (int)cell.getNumericCellValue() +"|";
						}
						else if(cell.getCellTypeEnum()== CellType.NUMERIC)
					
							res = res + (int)cell.getNumericCellValue() +"|";
						else if(cell.getCellTypeEnum()==CellType.BLANK)
							if(res.length()>0)
								res = res + "*|";
						else if(cell.getCellTypeEnum()==CellType._NONE)
							res = res + "*|";
						else if(cell.getCellTypeEnum()==CellType.FORMULA)
							if(cell.getCachedFormulaResultTypeEnum()== CellType.NUMERIC)
								res = res + (int)cell.getNumericCellValue() +"|";
							else
								res = res + cell.getStringCellValue()+"|";
						else
							if(res.length()>0)
								res = res + "*|";
					}
					continuer = true;
				}
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		
		//System.out.println("res : "+res);
		if(res.length()>0)
			return res.substring(0, res.length()-1);
		else
			return "";
	}
	
	
    public static void main(String[] args) {
    	String dir = System.getProperty("user.dir")+ File.separator;
    	String filepath = dir +"files"+File.separator+"Sujet_M1ILC_2017.xlsx";
		String onglet = "";
		XSSFSheet sheet;
		ArrayList<String> papers = new ArrayList<String>();
		System.out.println(filepath);
    	
    	try 
    	{
			File excel = new File(filepath);
			 wb = (XSSFWorkbook) WorkbookFactory.create(excel);
			 for(int i = 0; i < wb.getNumberOfSheets() ; i++)
			 {
				 sheet = wb.getSheetAt(i);
				 onglet = sheet.getSheetName();
				 if(onglet.equals("accepted papers"))
				 {
					 
				 }
				 else if(onglet.equals("All e-Tracks"))
				 {
					 
				 }
				 else
				 {
					 papers.addAll(Lignes(onglet, TypeObject.Papers));
				 }
				 
			 }
			 Path file = Paths.get(dir + "papers.txt");
			 System.out.println(file);
			 Files.write(file, papers, Charset.forName("UTF-8"));
		} 
    	catch (EncryptedDocumentException e) 
    	{
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
    	catch (InvalidFormatException e) 
    	{
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
    	catch (IOException e) 
    	{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }
}
