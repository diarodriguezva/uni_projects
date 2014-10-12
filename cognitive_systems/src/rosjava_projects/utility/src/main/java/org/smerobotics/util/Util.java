package org.smerobotics.util;

import static argo.jdom.JsonNodeFactories.field;
import static argo.jdom.JsonNodeFactories.object;
import static argo.jdom.JsonNodeFactories.string;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;

import argo.format.CompactJsonFormatter;
import argo.format.JsonFormatter;
import argo.format.PrettyJsonFormatter;
import argo.jdom.JdomParser;
import argo.jdom.JsonField;
import argo.jdom.JsonNode;
import argo.jdom.JsonNodeSelector;
import argo.jdom.JsonNodeSelectors;
import argo.jdom.JsonRootNode;
import argo.saj.InvalidSyntaxException;

public class Util {
	
	private static final JdomParser JDOM_PARSER = new JdomParser();
	private static final JsonNodeSelector<JsonNode,String> JSON_SEL_OWL = 
			JsonNodeSelectors.aStringNode("owl");
	private static final JsonFormatter JSON_FORMATTER_PRETTY = 
			new PrettyJsonFormatter();
	private static final JsonFormatter JSON_FORMATTER_COMPACT = 
			new CompactJsonFormatter();
	
	public static String format(JsonRootNode jsonRoot, boolean compact) {

		String formattedJson = null;

		if (jsonRoot != null) {

			if (compact) {
				formattedJson = JSON_FORMATTER_COMPACT.format(jsonRoot);
			} else {
				formattedJson = JSON_FORMATTER_PRETTY.format(jsonRoot);	
			}

		}

		return formattedJson;

	}
	
	public static String getJsonString(String[] params, String[] values) {
		
		String result = null;
		
		if (params != null && values != null && params.length == values.length) { 

			ArrayList<JsonField> list = new ArrayList<JsonField>();

			for (int i=0;i<params.length;i++) {
				list.add(field(params[i], string(values[i])));	
			}
			JsonRootNode json = object(list);
			
			result = format(json, true);
			
		}
		
		return result;
		
	}
	
	public static String getOwlValue(String jsonContent) 
			throws IllegalArgumentException, InvalidSyntaxException {

		String owl = null;

		if (jsonContent != null) {
			
			JsonRootNode json = JDOM_PARSER.parse(jsonContent.toString());
			owl = JSON_SEL_OWL.getValue(json);
			
		}

		return owl;

	}
	
	public static String getLocalRosPackagePath(String rosPackageName) {

		String dir = null;

		try {	

			// try to find package using rospack
			String line;
			Process get_path = new ProcessBuilder( "rospack", "find", rosPackageName).start();

			try {
				BufferedReader pathreader = new BufferedReader(new InputStreamReader(get_path.getInputStream(), "UTF-8"));

				if( (line = pathreader.readLine()) != null) {
					dir = line+File.separator;
				}
			} finally {
				if (get_path != null) {
					get_path.getInputStream().close();	
				}
			}

		} catch (IOException e) {
			e.printStackTrace(System.err);
		}

		return dir;

	}
	
	public static String getLocalRosjavaProjectPath(String packageName,
			String projectName) {

		String dir = null;

		try {

			String line;
			Process get_path = new ProcessBuilder("rospack", "find",
					packageName).start();

			try {

				BufferedReader pathreader = new BufferedReader(
						new InputStreamReader(get_path.getInputStream(),
								"UTF-8"));

				if ((line = pathreader.readLine()) != null) {
					dir = line + File.separator + projectName + File.separator;

				}

			} finally {
				if (get_path != null) {
					get_path.getInputStream().close();
				}
			}

		} catch (IOException e) {
			e.printStackTrace(System.err);
		}

		return dir;

	}
	
	public static String getContentFromOwlFile(String fileName) {

		String owl = null;
		BufferedReader br = null;
		
		try {
			final File f = new File(fileName);
			br = new BufferedReader(new FileReader(f));
			
			String line = null;
			StringBuilder content = new StringBuilder();
			while ((line = br.readLine()) != null) {
				content.append(line);
			}
			
			owl = content.toString();
			
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (br != null) {
				try {
					br.close();
				} catch (IOException e) {}	
			}
		}
		
		return owl;
		
	}
	
	public static byte[] getContentFromBinaryFile(String fileName) {

		byte[] data = null;

		File file = new File(fileName);
		
		if (file == null || !file.exists()) {
			System.out.println("Error while trying to get content from file '" + fileName + "': file is null");
			return data;
		}

		long length = file.length();
		if (length > Integer.MAX_VALUE) {
			System.out.println("  File '"+fileName+"' is too " +
					"big to upload! Operation canceled.");
		} else {

			InputStream is = null;

			try {

				is = new FileInputStream(file);
				data = new byte[(int)length];

				int offset = 0;
				int numRead = 0;
				while (offset < data.length
						&& (numRead=is.read(data, offset, data.length-offset)) >= 0) {
					offset += numRead;
				}

				if (offset < data.length) {
					data = null;
					System.out.println("  Could not completely read file "+fileName);
				}

			} catch (FileNotFoundException e) {
				System.out.println("  Couldn't find file '"+ fileName +
						"'! Operation canceled.");
			} catch (IOException e) {
				System.out.println("  IOException occurred, while reading " +
						"from file '"+fileName+"'! Operation canceled.");
			} finally {
				if (is != null) {
					try {
						is.close();
					} catch (IOException e) {
					}	
				}
			}

		}

		return data;

	}

}
