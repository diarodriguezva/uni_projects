package de.tum.i6.cogsys.srvs;

import geometry_msgs.Pose;

import org.ros.exception.RemoteException;
import org.ros.exception.ServiceNotFoundException;
import org.ros.node.ConnectedNode;
import org.ros.node.service.ServiceClient;
import org.ros.node.service.ServiceResponseListener;
import org.smerobotics.util.srv.ServiceRequestBuilderFactory;

import world_model_srvs.GetTransform;
import world_model_srvs.GetTransformRequest;
import world_model_srvs.GetTransformResponse;

public class GetTransformRequestBuilderFactory extends ServiceRequestBuilderFactory {

	public static final String SERVICE_NAME_GET_TRANSFORM = "world_model/get_transform";
	private ServiceClient<GetTransformRequest, GetTransformResponse> clientGetTransform;

	private final Object sync = new Object();
	private volatile boolean responsePending = false;

	private Pose pose = null;
	
	@Override
	public synchronized void addServiceClients(ConnectedNode connectedNode) {

		if (clientGetTransform == null) {

			boolean found = false;

			while (!found) {

				try {

					clientGetTransform = connectedNode.newServiceClient(
							SERVICE_NAME_GET_TRANSFORM,
							GetTransform._TYPE);

					found = true;

					System.out.println("    Found service '"
							+ SERVICE_NAME_GET_TRANSFORM
							+ "'. (type: "
							+ GetTransform._TYPE + ")");

				} catch (ServiceNotFoundException e) {

					System.out.println("  Waiting for service '"
							+ SERVICE_NAME_GET_TRANSFORM
							+ "' to start up. (type: "
							+ GetTransform._TYPE + ")");

					try {
						Thread.sleep(3000);
					} catch (InterruptedException ie) {
					}

				}

			}

		}

	}

	@Override
	public synchronized void removeServiceClients() {

		if (clientGetTransform != null) {

			clientGetTransform.shutdown();
			clientGetTransform = null;

			System.out.println("  Shutdown service client '"
					+ SERVICE_NAME_GET_TRANSFORM
					+ "'. (type: "
					+ GetTransform._TYPE + ")");

		}

	}

	public Pose call(String baseFrame, String targetFrame) {

		Pose p = null;
		
		GetTransformRequest req = clientGetTransform.newMessage();
		req.setBaseFrame(baseFrame);
		req.setTargetFrame(targetFrame);

		synchronized (sync) {

			responsePending = true;

			clientGetTransform.call(req, new ServiceResponseListener<GetTransformResponse>() {

				@Override
				public void onSuccess(GetTransformResponse response) {

					synchronized (sync) {

						if (response.getSuccess()) {
							pose = response.getPose();	 
						} else {
							pose = null;
						}
						
						responsePending = false;
						sync.notifyAll();
					}

				}

				@Override
				public void onFailure(RemoteException e) {

					synchronized (sync) {
						pose = null;
						responsePending = false;
						sync.notifyAll();
					}

				}

			});

			while (responsePending) {
				try {
					sync.wait();
				} catch (InterruptedException e1) {
				}
			}

			p = pose;

		}

		return p;

	}

}
